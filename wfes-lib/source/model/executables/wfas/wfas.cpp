#include "wfas.h"

using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfas *wfas::execute()
{

    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigWfas::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    #ifdef OMP
        omp_set_num_threads(ConfigWfas::n_threads);
    #endif
        mkl_set_num_threads(ConfigWfas::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    return this->function();

}

ResultsWfas *wfas::function()
{

    dvec s_scal = ConfigWfas::s.array() * ConfigWfas::f.array();
    dvec u_scal = ConfigWfas::u.array() * ConfigWfas::f.array();
    dvec v_scal = ConfigWfas::v.array() * ConfigWfas::f.array();

    llong size = (2 * ConfigWfas::N.sum()) + ConfigWfas::num_comp;

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    dmat switching = dmat::Zero(ConfigWfas::num_comp, ConfigWfas::num_comp);
    for(llong i = 0; i < ConfigWfas::num_comp - 1; i++) {
        switching(i, i) = 1 - (1 / ConfigWfas::G(i));
        switching(i, i+1) = 1 / ConfigWfas::G(i);
    }
    switching(ConfigWfas::num_comp - 1, ConfigWfas::num_comp - 1) = 1 - (1 / ConfigWfas::G(ConfigWfas::num_comp - 1));

    wrightfisher::Matrix W = wrightfisher::Switching(ConfigWfas::N, wrightfisher::NON_ABSORBING,
            s_scal, ConfigWfas::h, u_scal, v_scal, switching, ConfigWfas::a, msg_level);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfas::output_Q)
        W.Q->saveMarket(ConfigWfas::path_output_Q);
    if (ConfigWfas::output_R)
        utils::writeMatrixToFile(W.R, ConfigWfas::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W.Q->subtractIdentity();


    dvec initial;
    if (ConfigWfesSingle::initial_distribution_csv.compare("") != 0) {
        initial = load_csv_col_vector(ConfigWfesSingle::initial_distribution_csv);
    } else if (ConfigWfas::p != 0) {
        llong p = ConfigWfas::p;
        initial = dvec::Zero(2 * ConfigWfas::N(0) + 1);
        initial[p] = 1;
    } else {
        initial = wrightfisher::Equilibrium(ConfigWfas::N(0), s_scal(0), ConfigWfas::h(0), u_scal(0), v_scal(0), ConfigWfas::a, msg_level);
    }

    // llong n_rhs = 2 * population_sizes(0) + 1;
    llong n_rhs = 2 * ConfigWfas::N(0) + 1;
    // llong n_rhs = 2 * population_sizes(ConfigWfas::num_comp - 1) + 1;

    Solver* solver = SolverFactory::createSolver(ConfigWfas::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfas::vienna_solver, "", n_rhs);

    solver->preprocess();

    // dmat R = dmat::Identity(size, 2 * population_sizes(ConfigWfas::num_comp - 1) + 1).reverse() * (1 / t(ConfigWfas::num_comp - 1));
    llong nk = 2 * ConfigWfas::N(ConfigWfas::num_comp - 1) + 1;
    // SparseMatrix R = SparseMatrix::LeftPaddedDiagonal(nk, 1 / t(ConfigWfas::num_comp - 1), size - nk);
    // if(output_R_f) R.save_market(args::get(output_R_f));

    dmat id = dmat::Identity(n_rhs, size);

    dmat B = solver->solve_multiple(id, true);

    // if(output_N_f) write_matrix_to_file(Nt, args::get(output_N_f));

    B /= ConfigWfas::G(ConfigWfas::num_comp - 1);

    // std::cout << eq.rows() << " x " << eq.cols() << std::endl;
    // std::cout << B.transpose().rightCols(nk).rows() << " x " << B.transpose().rightCols(nk).cols() << std::endl;
    dvec d = initial.transpose() * B.transpose().rightCols(nk);

    // dvec d = B.transpose().rightCols(nk).row(0);


    llong lt = ConfigWfas::num_comp - 1;

    if (ConfigWfas::f(lt) != 1) {
        llong n = 2 * ConfigWfas::N(lt) + 1;
        llong m = 2 * (ConfigWfas::N(lt) * ConfigWfas::G(lt)) + 1;
        wrightfisher::Matrix sw_up = wrightfisher::Single(ConfigWfas::N(lt), ConfigWfas::N(lt) * ConfigWfas::G(lt),
                wrightfisher::NON_ABSORBING, ConfigWfas::s(lt), ConfigWfas::h(lt), ConfigWfas::u(lt), ConfigWfas::v(lt), true, ConfigWfas::a, msg_level);

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

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if(ConfigWfas::output_Dist) {
        utils::writeVectorToFile(d, ConfigWfas::path_output_Dist);
    }

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return new ResultsWfas(d, dt.count());
}
