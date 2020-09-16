#include "wfes_single.h"

#include <config/config.h>


using namespace wfes::wrightfisher;
using namespace wfes::solver;
using namespace wfes::sparsematrix;
using namespace wfes::pardiso;
using namespace wfes::config;
using namespace wfes;

Results* wfes_single::execute()
{
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = Config::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // If force is not activated, show error when values are not in expected ranges.
    this->force();

    // Set number of threads for intel MKL Pardiso.
    #ifdef OMP
        omp_set_num_threads(Config::n_threads);
    #endif
        mkl_set_num_threads(Config::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Set value for starting copies if the user has provided an initial distribution,
    // load it and calculate starting copies p.
    this->calculateStartingCopies();

    // Save initial distribution if resquested by the user.
    if (Config::output_I)
        utils::writeVectorToFile(starting_copies_p, Config::path_output_I);

    // Set value of z if the user has provided an initial distribution,
    // load it and calculate z value.
    this->calculateZ();

    // All cases (models) are wrapped in this switch instruction.
    switch(Config::modelType) {
        case ModelType::FIXATION:
            return this->fixation();
        case ModelType::ABSORPTION:
            return this->absorption();
        case ModelType::FUNDAMENTAL:
            return this->fundamental();
        case ModelType::EQUILIBRIUM:
            return this->equilibrium();
        case ModelType::ESTABLISHMENT:
            return this->establishment();
        case ModelType::ALLELE_AGE:
            return this->alleleAge();
        case ModelType::NON_ABSORBING:
            return this->nonAbsorbing();

        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelType::NONE:
        default:
            // TODO Show error as dialog.
            return new Results();
    }

    // If for some reason the code reaches this line (it shouldn't because all cases are covered by the switch),
    // return default results, which is formed by nan values, so the GUI does not show anything.
    return new Results();
}

Results *wfes_single::fixation()
{
    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix W = wrightfisher::Single(Config::population_size, Config::population_size, wrightfisher::FIXATION_ONLY, Config::s, Config::h, Config::u, Config::v,
                              Config::rem, Config::a, Config::verbose, Config::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_Q)
        W.Q->saveMarket(Config::path_output_Q);
    if (Config::output_R)
        utils::writeMatrixToFile(W.R, Config::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W.Q->subtractIdentity();

    llong size = (2 * Config::population_size);

    Solver *solver = wfes::solver::SolverFactory::createSolver(Config::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    solver->preprocess();

    dvec id(size);
    dmat N_mat(1, size);

    id.setZero();
    id(Config::starting_copies) = 1;
    N_mat.row(0) = solver->solve(id, true);
    dvec N1 = N_mat.row(0);
    dvec N2 = solver->solve(N1, true);
    double T_fix = N1.sum();
    double T_var = ((2 * N2.sum()) - N1.sum()) - pow(N1.sum(), 2);

    double rate = 1.0 / T_fix;
    double T_std = sqrt(T_var);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_N)
        utils::writeMatrixToFile(N_mat, Config::path_output_N);
    if (Config::output_B) {
        dvec B = dvec::Ones(size);
        utils::writeVectorToFile(B, Config::path_output_B);
    }

    delete solver;

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    Results* res = new Results(Config::modelType, T_fix, T_std, rate, dt.count());

    if(Config::output_Res)
       utils::writeResultsToFile(res, Config::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

Results *wfes_single::absorption()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix W = wrightfisher::Single(Config::population_size, Config::population_size, wrightfisher::BOTH_ABSORBING, Config::s, Config::h, Config::u, Config::v,
                              Config::rem, Config::a, Config::verbose, Config::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_Q)
        W.Q->saveMarket(Config::path_output_Q);
    if (Config::output_R)
        utils::writeMatrixToFile(W.R, Config::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W.Q->subtractIdentity();

    llong size = (2 * Config::population_size) - 1;

    Solver* solver = SolverFactory::createSolver(Config::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    solver->preprocess();

    dvec R_ext = W.R.col(0);
    dvec B_ext = solver->solve(R_ext, false);
    dvec B_fix = dvec::Ones(size) - B_ext;
    dvec id(size);

    // integrate over starting number of copies
    double P_ext = 0;
    double P_fix = 0;
    double T_abs = 0;
    double T_ext = 0;
    double T_fix = 0;
    double T_abs_var = 0;
    double T_ext_var = 0;
    double T_fix_var = 0;
    double N_ext = 0;

    dmat N_mat(z, size);
    dmat E_ext_mat(z, size);
    dmat E_fix_mat(z, size);
    dmat N2_mat(z, size);
    if (!Config::starting_copies) {
        for (llong i = 0; i < z; i++) {
            double p_i = starting_copies_p(i);
            id.setZero();
            id(i) = 1;

            N_mat.row(i) = solver->solve(id, true);
            dvec N1 = N_mat.row(i);
            N2_mat.row(i) = solver->solve(N1, true);
            dvec N2 = N2_mat.row(i);

            T_abs += N1.sum() * p_i;
            T_abs_var += (2 * N2.sum() - N1.sum()) - pow(N1.sum(), 2) * p_i;

            P_ext += B_ext(i) * p_i;
            dvec E_ext = B_ext.array() * N1.array() / B_ext(i);
            E_ext_mat.row(i) = E_ext;
            dvec E_ext_var = B_ext.array() * N2.array() / B_ext(i);
            T_ext += E_ext.sum() * p_i;
            T_ext_var += ((2 * E_ext_var.sum() - E_ext.sum()) - pow(E_ext.sum(), 2)) * p_i;

            dvec C_ext = E_ext.array() * dvec::LinSpaced(size, 1, size).array();
            N_ext += p_i * C_ext.sum();

            P_fix += B_fix(i) * p_i;
            dvec E_fix = B_fix.array() * N1.array() / B_fix(i);
            E_fix_mat.row(i) = E_fix;
            dvec E_fix_var = B_fix.array() * N2.array() / B_fix(i);
            T_fix += E_fix.sum() * p_i;
            T_fix_var += ((2 * E_fix_var.sum() - E_fix.sum()) - pow(E_fix.sum(), 2)) * p_i;

        }
    } else {
        // TODO: combine this with the previous clause
        id.setZero();
        id(Config::starting_copies) = 1;
        N_mat.row(0) = solver->solve(id, true);
        dvec N1 = N_mat.row(0);
        N2_mat.row(0) = solver->solve(N1, true);
        dvec N2 = N2_mat.row(0);

        T_abs = N1.sum();
        T_abs_var = (2 * N2.sum() - N1.sum()) - pow(N1.sum(), 2);

        P_ext = B_ext(Config::starting_copies);
        dvec E_ext = B_ext.array() * N1.array() / B_ext(Config::starting_copies);
        E_ext_mat.row(0) = E_ext;
        dvec E_ext_var = B_ext.array() * N2.array() / B_ext(Config::starting_copies);
        T_ext = E_ext.sum();
        T_ext_var = (2 * E_ext_var.sum() - E_ext.sum()) - pow(E_ext.sum(), 2);

        P_fix = B_fix(Config::starting_copies);
        dvec E_fix = B_fix.array() * N1.array() / B_fix(Config::starting_copies);
        E_fix_mat.row(0) = E_fix;
        dvec E_fix_var = B_fix.array() * N2.array() / B_fix(Config::starting_copies);
        T_fix = E_fix.sum();
        T_fix_var = (2 * E_fix_var.sum() - E_fix.sum()) - pow(E_fix.sum(), 2);

        dvec C_ext = E_ext.array() * dvec::LinSpaced(size, 1, size).array();
        N_ext = C_ext.sum();
        // N_ext = (N_mat.row(0) * B_ext * dvec::LinSpaced(size, 1, size)).sum() /
        // B_ext(starting_copies);
    }

    double T_abs_std = sqrt(T_abs_var);
    double T_ext_std = sqrt(T_ext_var);
    double T_fix_std = sqrt(T_fix_var);

    N_ext /= (1 / (2 * Config::population_size * Config::v)) + T_ext;

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_N)
        utils::writeMatrixToFile(N_mat, Config::path_output_N);
    if (Config::output_N_ext)
        utils::writeMatrixToFile(E_ext_mat, Config::path_output_N_ext);
    if (Config::output_N_fix)
        utils::writeMatrixToFile(E_fix_mat, Config::path_output_N_fix);
    if (Config::output_B) {
        dmat B(size, 2);
        B.col(0) = B_ext;
        B.col(1) = B_fix;
        utils::writeMatrixToFile(B, Config::path_output_B);
    }

    delete solver;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    Results* res = new Results(Config::modelType, P_ext, P_fix, T_abs, T_abs_std, T_ext, T_ext_std, N_ext, T_fix, T_fix_std, dt.count());

    if(Config::output_Res)
       utils::writeResultsToFile(res, Config::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

Results *wfes_single::fundamental()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    llong size = (2 * Config::population_size) - 1;
    wrightfisher::Matrix W = wrightfisher::Single(Config::population_size, Config::population_size, wrightfisher::BOTH_ABSORBING, Config::s, Config::h, Config::u, Config::v,
                              Config::rem, Config::a, Config::verbose, Config::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_Q)
        W.Q->saveMarket(Config::path_output_Q);
    if (Config::output_R)
        utils::writeMatrixToFile(W.R, Config::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W.Q->subtractIdentity();

    Solver* solver = SolverFactory::createSolver(Config::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    solver->preprocess();
    dmat N(size, size);
    dvec id(size);
    for (llong i = 0; i < size; i++) {
        id.setZero();
        id(i) = 1;
        N.row(i) = solver->solve(id, true);
    }

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_N)
        utils::writeMatrixToFile(N, Config::path_output_N);

    if (Config::output_V) {
        dvec Ndg = (2 * N.diagonal().array()) - 1;
        dmat Nsq = N.array().square();
        dmat V = (N * diagmat(Ndg)) - Nsq;

        utils::writeMatrixToFile(V, Config::path_output_V);
    }
    delete solver;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return new Results(dt.count());
}

Results *wfes_single::equilibrium()
{
    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    llong size = (2 * Config::population_size) + 1;
    wrightfisher::Matrix W = wrightfisher::EquilibriumSolvingMatrix(Config::population_size, Config::s, Config::h, Config::u, Config::v, Config::a, Config::verbose, Config::b);

    Solver* solver = SolverFactory::createSolver(Config::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    solver->preprocess();
    dvec O = dvec::Zero(size);
    O(size - 1) = 1;

    dvec pi = solver->solve(O, true);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_E) {
        utils::writeVectorToFile(pi, Config::path_output_E);
    }

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    // Calculate expected frequency
    double e_freq = 0.0;
    for (llong i = 0; i < size; i++) {
        e_freq += i * pi[i];
    }
    e_freq /= (size - 1);

    delete solver;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    Results* res = new Results(Config::modelType, e_freq, (1.0 - e_freq), dt.count());

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if(Config::output_Res)
       utils::writeResultsToFile(res, Config::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

Results *wfes_single::establishment()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    // Full Wright-Fisher
    wrightfisher::Matrix W_full = wrightfisher::Single(Config::population_size, Config::population_size, wrightfisher::BOTH_ABSORBING, Config::s, Config::h,
                                   Config::u, Config::v, Config::rem, Config::a, Config::verbose, Config::b);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W_full.Q->subtractIdentity();

    llong size = (2 * Config::population_size) - 1;

    Solver* solver_full = SolverFactory::createSolver(Config::library, *(W_full.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    solver_full->preprocess();

    dvec R_full_fix = W_full.R.col(1);
    dvec B_full_fix = solver_full->solve(R_full_fix, false);
    dvec B_full_ext = dvec::Constant(size, 1) - B_full_fix;
    dvec id_full(size);

    // establishment
    llong est_idx = 0;
    // find closest to k / (1 + k)
    // cout << odds_ratio / (1 + odds_ratio) << endl;
    dvec B_est_closest = B_full_fix - dvec::Constant(size, Config::odds_ratio / (1 + Config::odds_ratio));
    B_est_closest.array().abs().minCoeff(&est_idx);

    if (est_idx == 1) {
        throw wfes::exception::Error("Establishment is near-certain: establishment-count is 1");
    }
    if (z >= est_idx) {
        throw wfes::exception::Error("Establishment can be reached by mutation alone");
    }

    // Since the B indexes begin at 1
    est_idx++;
    // cout << est_idx << endl;
    double est_freq = (double)(est_idx) / (2 * Config::population_size);

    // post-establishment time before absorption
    id_full.setZero();
    id_full(est_idx) = 1;
    dvec N1_aft_est = solver_full->solve(id_full, true);
    dvec N2_aft_est = solver_full->solve(N1_aft_est, true);

    // Segregation
    double T_seg = N1_aft_est.sum();
    double T_seg_var = (2 * N2_aft_est.sum() - N1_aft_est.sum()) - pow(N1_aft_est.sum(), 2);
    double T_seg_std = sqrt(T_seg_var);

    dvec E_seg_ext = B_full_ext.array() * N1_aft_est.array() / B_full_ext(est_idx);
    dvec E_seg_ext_var = B_full_ext.array() * N2_aft_est.array() / B_full_ext(est_idx);
    double T_seg_ext = E_seg_ext.sum();
    double T_seg_ext_var =
        (2 * E_seg_ext_var.sum() - E_seg_ext.sum()) - pow(E_seg_ext.sum(), 2);
    double T_seg_ext_std = sqrt(T_seg_ext_var);

    dvec E_seg_fix = B_full_fix.array() * N1_aft_est.array() / B_full_fix(est_idx);
    dvec E_seg_fix_var = B_full_fix.array() * N2_aft_est.array() / B_full_fix(est_idx);
    double T_seg_fix = E_seg_fix.sum();
    double T_seg_fix_var =
        (2 * E_seg_fix_var.sum() - E_seg_fix.sum()) - pow(E_seg_fix.sum(), 2);
    double T_seg_fix_std = sqrt(T_seg_fix_var);

    // Truncated model
    wrightfisher::Matrix W_tr = wrightfisher::Truncated(Config::population_size, Config::population_size, est_idx, Config::s, Config::h, Config::u, Config::v, Config::rem,
                                    Config::a, Config::verbose, Config::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_Q)
        W_tr.Q->saveMarket(Config::path_output_Q);
    if (Config::output_R)
        utils::writeMatrixToFile(W_tr.R, Config::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    // To test
    // cout << W_tr.R.col(0) + W_tr.Q.dense().rowwise().sum() + W_tr.R.col(1) << endl;
    // cout << W.Q.dense() << endl;

    W_tr.Q->subtractIdentity();

    Solver* solver_tr = SolverFactory::createSolver(Config::library, *(W_tr.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    solver_tr->preprocess();

    dvec R_est = W_tr.R.col(1);
    dvec B_est = solver_tr->solve(R_est, false);
    dvec B_ext = dvec::Ones(est_idx - 1) - B_est;

    // integrate over starting number of copies
    double P_ext = 0;
    double P_est = 0;
    double T_ext = 0;
    double T_est = 0;
    double T_ext_var = 0;
    double T_est_var = 0;

    dmat N_mat(z, est_idx - 1);
    dmat E_ext_mat(z, est_idx - 1);
    dmat E_est_mat(z, est_idx - 1);
    dmat N2_mat(z, est_idx - 1);

    dvec id(est_idx);
    if (!Config::starting_copies) {
        for (llong i = 0; i < z; i++) {
            double p_i = starting_copies_p(i);
            id.setZero();
            id(i) = 1;

            N_mat.row(i) = solver_tr->solve(id, true);
            dvec N1 = N_mat.row(i);
            N2_mat.row(i) = solver_tr->solve(N1, true);
            dvec N2 = N2_mat.row(i);

            P_ext += B_ext(i) * p_i;
            dvec E_ext = B_ext.array() * N1.array() / B_ext(i);
            E_ext_mat.row(i) = E_ext;
            dvec E_ext_var = B_ext.array() * N2.array() / B_ext(i);
            T_ext += E_ext.sum() * p_i;
            T_ext_var +=
                (((2 * E_ext_var.sum() - E_ext.sum()) * p_i) - pow(E_ext.sum() * p_i, 2));

            P_est += B_est(i) * p_i;
            dvec E_est = B_est.array() * N1.array() / B_est(i);
            E_est_mat.row(i) = E_est;
            dvec E_est_var = B_est.array() * N2.array() / B_est(i);
            T_est += E_est.sum() * p_i;
            T_est_var +=
                (((2 * E_est_var.sum() - E_est.sum()) * p_i) - pow(E_est.sum() * p_i, 2));
        }
    } else {
        // TODO: combine this with the previous clause
        id.setZero();
        id(Config::starting_copies) = 1;
        N_mat.row(0) = solver_tr->solve(id, true);
        dvec N1 = N_mat.row(0);
        N2_mat.row(0) = solver_tr->solve(N1, true);
        dvec N2 = N2_mat.row(0);

        P_ext = B_ext(Config::starting_copies);
        dvec E_ext = B_ext.array() * N1.array() / B_ext(Config::starting_copies);
        E_ext_mat.row(0) = E_ext;
        dvec E_ext_var = B_ext.array() * N2.array() / B_ext(Config::starting_copies);
        T_ext = E_ext.sum();
        T_ext_var = (2 * E_ext_var.sum() - E_ext.sum()) - pow(E_ext.sum(), 2);

        P_est = B_est(Config::starting_copies);
        dvec E_est = B_est.array() * N1.array() / B_est(Config::starting_copies);
        E_est_mat.row(0) = E_est;
        dvec E_est_var = B_est.array() * N2.array() / B_est(Config::starting_copies);
        T_est = E_est.sum();
        T_est_var = (2 * E_est_var.sum() - E_est.sum()) - pow(E_est.sum(), 2);
    }
    double T_est_std = sqrt(T_est_var);

    delete solver_full;
    delete solver_tr;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    Results* res = new Results(Config::modelType, est_freq, P_est, T_seg, T_seg_std,
                               T_seg_ext, T_seg_ext_std, T_seg_fix, T_seg_fix_std, T_est, T_est_std, dt.count());

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if(Config::output_Res)
       utils::writeResultsToFile(res, Config::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

Results *wfes_single::alleleAge()
{
    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    if (Config::observed_copies < 1 || Config::observed_copies > Config::population_size) {
        throw wfes::exception::Error("x (observed copies) must be between 1 and N");
    }
    llong x = Config::observed_copies - 1;

    llong size = (2 * Config::population_size) - 1;
    wrightfisher::Matrix W = wrightfisher::Single(Config::population_size, Config::population_size, wrightfisher::BOTH_ABSORBING, Config::s, Config::h, Config::u, Config::v,
                              Config::rem, Config::a, Config::verbose, Config::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_Q)
        W.Q->saveMarket(Config::path_output_Q);
    if (Config::output_R)
        utils::writeMatrixToFile(W.R, Config::path_output_R);
    dvec Q_x = W.Q-> getColCopy(x);
    W.Q->subtractIdentity();

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    Solver* solver = SolverFactory::createSolver(Config::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, Config::vienna_solver);

    solver->preprocess();

    W.Q->subtractIdentity();
    dvec Q_I_x = W.Q->getColCopy(x);
    Q_I_x(x) += 1;
    dvec A_x = W.Q->multiply(Q_I_x);

    double E_allele_age = 0;
    double S_allele_age = 0;
    if (!Config::starting_copies) {
        // Iterate over starting states
        for (llong i = 0; i < z; i++) {
            dvec e_p = dvec::Zero(size);
            e_p(i) = 1;

            dvec M1 = solver->solve(e_p, true);
            dvec M2 = solver->solve(M1, true);

            double mu1 = M2.dot(Q_x) / M1(x);

            dvec M3 = solver->solve(M2, true);

            double mu2 = sqrt((M3.dot(A_x) / M1(x)) - pow(mu1, 2));

            E_allele_age += mu1 * starting_copies_p(i);
            S_allele_age += mu2 * starting_copies_p(i);
        }
    } else {
        dvec e_p = dvec::Zero(size);
        e_p(Config::starting_copies) = 1;

        dvec M1 = solver->solve(e_p, true);
        dvec M2 = solver->solve(M1, true);

        E_allele_age = M2.dot(Q_x) / M1(x);

        dvec M3 = solver->solve(M2, true);

        S_allele_age = sqrt((M3.dot(A_x) / M1(x)) - pow(E_allele_age, 2));
    }

    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    Results* res = new Results(Config::modelType, E_allele_age, S_allele_age, true, dt.count());

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if(Config::output_Res)
       utils::writeResultsToFile(res, Config::path_output_Res);

    delete solver;

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

Results *wfes_single::nonAbsorbing()
{
    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix W = wrightfisher::Single(Config::population_size, Config::population_size, wrightfisher::NON_ABSORBING, Config::s, Config::h, Config::u, Config::v,
                              Config::rem, Config::a, Config::verbose, Config::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (Config::output_Q)
        W.Q->saveMarket(Config::path_output_Q);

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return new Results(dt.count());
}

void wfes_single::force()
{
    if (!Config::force) {
        if (Config::population_size > 500000) {
            // TODO Show as dialog.
            throw exception::Error("Population size is quite large - the computations will take a long "
                              "time. Use --force to ignore");
        }
        double max_mu = std::max(Config::u, Config::v);
        if ((4 * Config::population_size * max_mu) > 1) {
            // TODO Show as dialog.
            throw exception::Error("The mutation rate might violate the Wright-Fisher assumptions. Use "
                              "--force to ignore");
        }
        if ((2 * Config::population_size * Config::s) <= -100) {
            // TODO Show as dialog.
            throw exception::Error("The selection coefficient is quite negative. Fixations might be "
                              "impossible. Use --force to ignore");
        }
        if (Config::a > 1e-5) {
            // TODO Show as dialog.
            throw exception::Error("Zero cutoff value is quite high. This might produce inaccurate "
                              "results. Use --force to ignore");
        }
    }

}

void wfes_single::calculateStartingCopies()
{
    if (Config::initial_distribution_csv.compare("") != 0) {
        // TODO Show as dialog.
        // cout << "Reading initial from file" << args::get(initial_distributon_csv_f) << "" <<
        // endl;
        starting_copies_p = load_csv_col_vector(Config::initial_distribution_csv);
    } else {
        dvec first_row = wrightfisher::binom_row(2 * Config::population_size, wrightfisher::psi_diploid(0, Config::population_size, Config::s, Config::h, Config::u, Config::v), Config::a).Q;
        starting_copies_p = first_row.tail(first_row.size() - 1); // renormalize
        starting_copies_p /= 1 - first_row(0);
    }
}

void wfes_single::calculateZ()
{
    // Set value of z if the user has provided an initial distribution,
    // load it and calculate z value.
    z = 0;
    if (Config::initial_distribution_csv.compare("") != 0) {
        z = starting_copies_p.size();
    } else if (Config::integration_cutoff <= 0 || Config::v == 0) { // no integration
        z = 1;
        starting_copies_p[0] = 1;
    } else {
        int i = 0;
        while(i < starting_copies_p.size()) {
            if(starting_copies_p(i) > Config::integration_cutoff)
                z++;
            else break;
            i++;
        }
    }
    if (Config::starting_copies)
        z = 1;
}
