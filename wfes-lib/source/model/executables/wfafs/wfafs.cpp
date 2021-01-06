#include "wfafs.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfafs *wfafs::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfafs::n_threads);
    mkl_set_num_threads(ConfigWfafs::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Start execution.
    return this->function();

}

ResultsWfafs *wfafs::function() {
    try {
        // Population-scaled values.
        dvec s = ConfigWfafs::s;
        dvec u = ConfigWfafs::u;
        dvec v = ConfigWfafs::v;
        if(GlobalConfiguration::populationScaled) {
            for (int i = 0; i < ConfigWfafs::num_comp; i++) {
                s[i] = ConfigWfafs::s[i] / (2.0 * ConfigWfafs::N[i]);
                u[i] = ConfigWfafs::u[i] / (4.0 * ConfigWfafs::N[i]);
                v[i] = ConfigWfafs::v[i] / (4.0 * ConfigWfafs::N[i]);
            }
        }

        dvec s_scal = s.array() * ConfigWfafs::f.array();
        dvec u_scal = u.array() * ConfigWfafs::f.array();
        dvec v_scal = v.array() * ConfigWfafs::f.array();

        dvec ps_tmp = ConfigWfafs::N.cast<double>().array() / ConfigWfafs::f.array();
        lvec popSizes = ps_tmp.cast<llong>();
        dvec t_tmp = ConfigWfafs::G.cast<double>().array() / ConfigWfafs::f.array();
        dvec gens = t_tmp;

        llong size = (2 * popSizes.sum()) + ConfigWfafs::num_comp;

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfafs();
        }

        dmat switching = dmat::Zero(ConfigWfafs::num_comp, ConfigWfafs::num_comp);
        for(llong i = 0; i < ConfigWfafs::num_comp - 1; i++) {
            if(QThread::currentThread()->isInterruptionRequested()) {
                this->notify(ExecutionStatus::ABORTED);
                return new ResultsWfafs();
            }
            switching(i, i) = 1 - (1 / gens(i));
            switching(i, i+1) = 1 / gens(i);
        }
        switching(ConfigWfafs::num_comp - 1, ConfigWfafs::num_comp - 1) = 1 - (1 / gens(ConfigWfafs::num_comp - 1));

        wrightfisher::Matrix W = wrightfisher::Switching(popSizes, wrightfisher::NON_ABSORBING,
                s_scal, ConfigWfafs::h, u_scal, v_scal, switching, ConfigWfafs::a, msg_level);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfafs::output_Q)
            utils::writeSparseMatrixToFile(W.Q, ConfigWfafs::path_output_Q, "WFAF-S");
        //if (ConfigWfafs::output_R)
        //    utils::writeMatrixToFile(W.R, ConfigWfafs::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfafs();
        }

        W.Q->subtractIdentity();


        dvec initial;
        if (ConfigWfafs::initial_distribution_csv.compare("") != 0) {
            initial = load_csv_col_vector(ConfigWfafs::initial_distribution_csv);
            // Check if Initial Distribution File (i) size is correct.
            if(initial.size() != ((2 * popSizes(0)) + 1)) {
                this->notify(ExecutionStatus::EXECUTION_ERROR);
                return new ResultsWfafs("Initial Probability Distribution (I) file must have " + std::to_string((2 * popSizes(0)) + 1) + " elements. Your file has " + std::to_string(initial.size()) + " elements.");
            }
        } else if (ConfigWfafs::p != 0) {
            llong p = ConfigWfafs::p;
            initial = dvec::Zero(2 * popSizes(0) + 1);
            initial[p] = 1;
        } else {
            initial = wrightfisher::Equilibrium(popSizes(0), s_scal(0), ConfigWfafs::h(0), u_scal(0), v_scal(0), ConfigWfafs::a, msg_level);
        }

        // llong n_rhs = 2 * population_sizes(0) + 1;
        llong n_rhs = 2 * popSizes(0) + 1;
        // llong n_rhs = 2 * population_sizes(ConfigWfafs::num_comp - 1) + 1;

        Solver* solver = SolverFactory::createSolver(ConfigWfafs::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfafs::vienna_solver, "", n_rhs);

        solver->preprocess();

        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfafs();
        }

        //dvec R_ext = W.R.col(0);
        //dvec B_ext = solver->solve(R_ext, false);
        //dvec B_fix = dvec::Ones(size) - B_ext;


        // dmat R = dmat::Identity(size, 2 * population_sizes(ConfigWfafs::num_comp - 1) + 1).reverse() * (1 / t(ConfigWfafs::num_comp - 1));
        llong nk = 2 * popSizes(ConfigWfafs::num_comp - 1) + 1;
        // SparseMatrix R = SparseMatrix::LeftPaddedDiagonal(nk, 1 / t(ConfigWfafs::num_comp - 1), size - nk);
        // if(output_R_f) R.save_market(args::get(output_R_f));

        dmat id = dmat::Identity(n_rhs, size);

        dmat B = solver->solve_multiple(id, true);

        // if(output_N_f) write_matrix_to_file(Nt, args::get(output_N_f));

        B /= gens(ConfigWfafs::num_comp - 1);

        // std::cout << eq.rows() << " x " << eq.cols() << std::endl;
        // std::cout << B.transpose().rightCols(nk).rows() << " x " << B.transpose().rightCols(nk).cols() << std::endl;
        dvec d = initial.transpose() * B.transpose().rightCols(nk);

        // dvec d = B.transpose().rightCols(nk).row(0);


        llong lt = ConfigWfafs::num_comp - 1;

        if (ConfigWfafs::f(lt) != 1) {
            llong n = 2 * popSizes(lt) + 1;
            llong m = 2 * (popSizes(lt) * gens(lt)) + 1;
            wrightfisher::Matrix sw_up = wrightfisher::SingleWfafs(popSizes(lt), popSizes(lt) * gens(lt), ConfigWfafs::N(lt), ConfigWfafs::N(lt),
                    wrightfisher::NON_ABSORBING, s(lt), ConfigWfafs::h(lt), u(lt), v(lt), true, ConfigWfafs::a, msg_level);

            // projected up
            dvec prj_u = sw_up.Q->multiply(d, true);

            if (!ConfigWfafs::no_proj) {
                // projected down
                dvec prj_d = dvec::Zero(n);

                double diag_f = (m-2)/(n-2);

                // how many states are we integrating into each prj_d state
                dvec row_integral_counts(n);
                for (llong i = 0; i < m-2; i++) {
                    llong j = int(i / diag_f);
                    row_integral_counts[j + 1] ++;
                }

                // multiply prj_d by the tall diagonal matrix
                prj_d[0] = prj_u[0]; prj_d[prj_d.size()-1] = prj_u[prj_u.size()-1];
                for (llong i = 0; i < m-2; i++) {
                    if(QThread::currentThread()->isInterruptionRequested()) {
                        this->notify(ExecutionStatus::ABORTED);
                        return new ResultsWfafs();
                    }
                    llong j = int(i / diag_f);
                    prj_d[j + 1] += prj_u[i + 1] / row_integral_counts[j + 1];

                }
                d = prj_d;
            } else {
                d = prj_u;
            }
        }

        // This is for chart visualization.
        QList<QPointF> dist;
        double minDist = std::numeric_limits<double>::max();
        double maxDist = std::numeric_limits<double>::min();
        for(int i = 0; i < d.size(); i++) {
            if(minDist >= d[i])
                minDist = d[i];
            if(maxDist <= d[i])
                maxDist = d[i];
            dist.append(QPointF(i+1, d[i]));
        }
        ChartResults::wfafsDist = dist;
        ChartResults::minMaxwfafsDist = QPointF(minDist, maxDist);
        // This is for chart visualization.

        dmat Nt(size, size);
        dvec id2(size);
        if (ConfigWfafs::output_N) {
            // Calculate fundamental matrix
            for (llong i = 0; i < size; i++) {
                id2.setZero();
                id2(i) = 1;
                Nt.row(i) = solver->solve(id2, true);
            }
        }

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfafs();
        }


        // Save data into file.
        if (ConfigWfafs::output_N)
            utils::writeMatrixToFile(Nt, ConfigWfafs::path_output_N, "WFAF-S");
        if (ConfigWfafs::output_B) {
            utils::writeMatrixToFile(B, ConfigWfafs::path_output_B, "WFAF-S");
        }
        if(ConfigWfafs::output_Dist) {
            utils::writeVectorToFile(d, ConfigWfafs::path_output_Dist, "WFAF-S");
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageB = nullptr, *imageN = nullptr;
            if(ConfigWfafs::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfafs::output_N) {
                imageN = utils::generateImage(Nt);
                ImageResults::N = imageN;
            }
            if(ConfigWfafs::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsWfafs(d, dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::EXECUTION_ERROR);
        return new ResultsWfafs(e.what());
    }
}
