#include "wfas.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfas *wfas::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfas::n_threads);
    mkl_set_num_threads(ConfigWfas::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Start execution.
    return this->function();

}

ResultsWfas *wfas::function() {
    try {
        // Population-scaled values.
        dvec s = ConfigWfas::s;
        dvec u = ConfigWfas::u;
        dvec v = ConfigWfas::v;
        if(GlobalConfiguration::populationScaled) {
            for (int i = 0; i < ConfigWfas::num_comp; i++) {
                s[i] = ConfigWfas::s[i] / (2.0 * ConfigWfas::N[i]);
                u[i] = ConfigWfas::u[i] / (4.0 * ConfigWfas::N[i]);
                v[i] = ConfigWfas::v[i] / (4.0 * ConfigWfas::N[i]);
            }
        }

        dvec s_scal = s.array() * ConfigWfas::f.array();
        dvec u_scal = u.array() * ConfigWfas::f.array();
        dvec v_scal = v.array() * ConfigWfas::f.array();

        dvec ps_tmp = ConfigWfas::N.cast<double>().array() / ConfigWfas::f.array();
        lvec popSizes = ps_tmp.cast<llong>();
        dvec t_tmp = ConfigWfas::G.cast<double>().array() / ConfigWfas::f.array();
        dvec gens = t_tmp;

        llong size = (2 * popSizes.sum()) + ConfigWfas::num_comp;

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        dmat switching = dmat::Zero(ConfigWfas::num_comp, ConfigWfas::num_comp);
        for(llong i = 0; i < ConfigWfas::num_comp - 1; i++) {
            switching(i, i) = 1 - (1 / gens(i));
            switching(i, i+1) = 1 / gens(i);
        }
        switching(ConfigWfas::num_comp - 1, ConfigWfas::num_comp - 1) = 1 - (1 / gens(ConfigWfas::num_comp - 1));

        wrightfisher::Matrix W = wrightfisher::Switching(popSizes, wrightfisher::NON_ABSORBING,
                s_scal, ConfigWfas::h, u_scal, v_scal, switching, ConfigWfas::a, msg_level);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfas::output_Q)
            W.Q->saveMarket(ConfigWfas::path_output_Q);
        //if (ConfigWfas::output_R)
        //    utils::writeMatrixToFile(W.R, ConfigWfas::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        W.Q->subtractIdentity();


        dvec initial;
        if (ConfigWfas::initial_distribution_csv.compare("") != 0) {
            initial = load_csv_col_vector(ConfigWfas::initial_distribution_csv);
        } else if (ConfigWfas::p != 0) {
            llong p = ConfigWfas::p;
            initial = dvec::Zero(2 * popSizes(0) + 1);
            initial[p] = 1;
        } else {
            initial = wrightfisher::Equilibrium(popSizes(0), s_scal(0), ConfigWfas::h(0), u_scal(0), v_scal(0), ConfigWfas::a, msg_level);
        }

        // llong n_rhs = 2 * population_sizes(0) + 1;
        llong n_rhs = 2 * popSizes(0) + 1;
        // llong n_rhs = 2 * population_sizes(ConfigWfas::num_comp - 1) + 1;

        Solver* solver = SolverFactory::createSolver(ConfigWfas::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfas::vienna_solver, "", n_rhs);

        solver->preprocess();

        //dvec R_ext = W.R.col(0);
        //dvec B_ext = solver->solve(R_ext, false);
        //dvec B_fix = dvec::Ones(size) - B_ext;


        // dmat R = dmat::Identity(size, 2 * population_sizes(ConfigWfas::num_comp - 1) + 1).reverse() * (1 / t(ConfigWfas::num_comp - 1));
        llong nk = 2 * popSizes(ConfigWfas::num_comp - 1) + 1;
        // SparseMatrix R = SparseMatrix::LeftPaddedDiagonal(nk, 1 / t(ConfigWfas::num_comp - 1), size - nk);
        // if(output_R_f) R.save_market(args::get(output_R_f));

        dmat id = dmat::Identity(n_rhs, size);

        dmat B = solver->solve_multiple(id, true);

        // if(output_N_f) write_matrix_to_file(Nt, args::get(output_N_f));

        B /= gens(ConfigWfas::num_comp - 1);

        // std::cout << eq.rows() << " x " << eq.cols() << std::endl;
        // std::cout << B.transpose().rightCols(nk).rows() << " x " << B.transpose().rightCols(nk).cols() << std::endl;
        dvec d = initial.transpose() * B.transpose().rightCols(nk);

        // dvec d = B.transpose().rightCols(nk).row(0);


        llong lt = ConfigWfas::num_comp - 1;

        if (ConfigWfas::f(lt) != 1) {
            llong n = 2 * popSizes(lt) + 1;
            llong m = 2 * (popSizes(lt) * gens(lt)) + 1;
            wrightfisher::Matrix sw_up = wrightfisher::Single(popSizes(lt), popSizes(lt) * gens(lt),
                    wrightfisher::NON_ABSORBING, s(lt), ConfigWfas::h(lt), u(lt), v(lt), true, ConfigWfas::a, msg_level);

            // projected up
            dvec prj_u = sw_up.Q->multiply(d, true);

            if (!ConfigWfas::no_proj) {
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
        ChartResults::wfasDist = dist;
        ChartResults::minMaxwfasDist = QPointF(minDist, maxDist);
        // This is for chart visualization.

        dmat Nt = dmat::Zero(n_rhs, size);
        if (ConfigWfas::output_N) {
            // Calculate fundamental matrix
            dmat Nt = dmat::Zero(n_rhs, size);
            for(llong i = 0; i < n_rhs; i++) {
                dvec id_tmp = id.col(i);
                Nt.col(i) = solver->solve(id_tmp, true);
            }
        }

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);


        // Save data into file.
        if (ConfigWfas::output_N)
            utils::writeMatrixToFile(Nt, ConfigWfas::path_output_N);
        if (ConfigWfas::output_B) {
            utils::writeMatrixToFile(B, ConfigWfas::path_output_B);
        }
        if(ConfigWfas::output_Dist) {
            utils::writeVectorToFile(d, ConfigWfas::path_output_Dist);
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageB = nullptr, *imageN = nullptr;
            if(ConfigWfas::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfas::output_N) {
                imageN = utils::generateImage(Nt);
                ImageResults::N = imageN;
            }
            if(ConfigWfas::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsWfas(d, dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfas(e.what());
    }
}
