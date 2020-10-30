#include "wfes_switching.h"

using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSwitching *wfes_switching::execute()
{
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigWfesSwitching::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    #ifdef OMP
        omp_set_num_threads(ConfigWfesSweep::n_threads);
    #endif
        mkl_set_num_threads(ConfigWfesSwitching::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    this->force();

    // dmat switching = GTR::Matrix(p, r);

    // switching.diagonal() = dvec::Zero(n_models);
    // switching /= switching.sum();
    dvec row_sums = ConfigWfesSwitching::r.rowwise().sum();
    for (llong i = 0; i < ConfigWfesSwitching::num_comp; i++) {
        for (llong j = 0; j < ConfigWfesSwitching::num_comp; j++) {
            ConfigWfesSwitching::r(i, j) /= row_sums(i);
        }
    }

    switch(ConfigWfesSwitching::modelType) {
        case ModelTypeWfesSwitching::FIXATION:
            return this->fixation();
        case ModelTypeWfesSwitching::ABSORPTION:
            return this->absorption();
        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypeWfesSwitching::NONE:
        default:
            // TODO Show error as dialog.
            return new ResultsWfesSwitching();
    }

}

ResultsWfesSwitching *wfes_switching::absorption()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix W = wrightfisher::Switching(ConfigWfesSwitching::N, wrightfisher::BOTH_ABSORBING,
            ConfigWfesSwitching::s, ConfigWfesSwitching::h, ConfigWfesSwitching::u, ConfigWfesSwitching::v, ConfigWfesSwitching::r, ConfigWfesSwitching::a, msg_level);

    // SI are start indeces - a vector of size n_models
    lvec si = startIndeces(2 * ConfigWfesSwitching::N - lvec::Ones(ConfigWfesSwitching::num_comp));

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfesSwitching::output_Q)
        W.Q->saveMarket(ConfigWfesSwitching::path_output_Q);
    if (ConfigWfesSwitching::output_R)
        utils::writeMatrixToFile(W.R, ConfigWfesSwitching::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W.Q->subtractIdentity();

    llong size = (2 * ConfigWfesSwitching::N.sum()) - ConfigWfesSwitching::num_comp;

    Solver* solver = SolverFactory::createSolver(ConfigWfesSwitching::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSwitching::vienna_solver);
    solver->preprocess();

    // Get initial probabilities of mu within each model
    lvec nnz_p0(ConfigWfesSwitching::num_comp);
    std::vector<dvec> p0(ConfigWfesSwitching::num_comp);
    for (llong i = 0; i < ConfigWfesSwitching::num_comp; i++) {
        llong pop_size = ConfigWfesSwitching::N(i);
        dvec first_row = wrightfisher::binom_row(2 * pop_size, wrightfisher::psi_diploid(0, pop_size, ConfigWfesSwitching::ConfigWfesSwitching::s(i), ConfigWfesSwitching::h(i), ConfigWfesSwitching::u(i), ConfigWfesSwitching::v(i)), ConfigWfesSwitching::a).Q;
        p0[i] = first_row.tail(first_row.size() - 1) / (1 - first_row(0)); // renormalize
        nnz_p0[i] = (p0[i].array() > ConfigWfesSwitching::c).count();
    }

    // extinction and fixation column for each submodel
    dmat B(size, ConfigWfesSwitching::num_comp * 2);
    for (llong i = 0; i < ConfigWfesSwitching::num_comp * 2; i++) {
        dvec R_col = W.R.col(i);
        B.col(i) = solver->solve(R_col, false);
    }

    std::map<llong, dvec> N_rows;
    std::map<llong, dvec> N2_rows;
    dvec id(size);
    for (llong i_ = 0; i_ < si.size(); i_++) {
        llong i = si[i_];
        for(llong o_ = 0; o_ < nnz_p0[i_]; o_++) {
            llong idx = i + o_;
            id.setZero();
            id(idx) = 1;
            N_rows[idx] = solver->solve(id, true);
            N2_rows[idx] = solver->solve(N_rows[idx], true);
        }
    }

    // absorbing extinction columns of B
    lvec ke = rangeStep(0, 2*ConfigWfesSwitching::num_comp, 2);
    // absorbing fixation columns of B
    lvec kf = rangeStep(1, 2*ConfigWfesSwitching::num_comp, 2);

    double P_ext = 0;
    double P_fix = 0;
    dvec P_cond_fix = dvec::Zero(ConfigWfesSwitching::num_comp);
    dvec P_cond_ext = dvec::Zero(ConfigWfesSwitching::num_comp);

    for (llong i_ = 0; i_ < si.size(); i_++) {
        llong i = si[i_];
        for(llong o_ = 0; o_ < nnz_p0[i_]; o_++) {
            double o = p0[i_](o_);
            llong idx = i + o_;

            double P_ext_i = 0;
            for (llong k_ = 0; k_ < ke.size(); k_++) {
                P_ext_i += B(idx, ke[k_]);
                P_cond_ext[k_] += B(idx, ke[k_]) * o * ConfigWfesSwitching::p[i_];
            }
            // P_cond_ext[i_] += P_ext_i * o;
            P_ext += P_ext_i * o * ConfigWfesSwitching::p[i_];

            double P_fix_i = 0;
            for (llong k_ = 0; k_ < kf.size(); k_++) {
                P_fix_i += B(idx, kf[k_]);
                P_cond_fix[k_] += B(idx, kf[k_]) * o * ConfigWfesSwitching::p[i_];
            }
            // P_cond_fix[i_] += P_fix_i * o;
            P_fix += P_fix_i * o * ConfigWfesSwitching::p[i_];
        }
    }

    // Summarize extinction and fixation absorption vectors
    dvec B_fix = dvec::Zero(size);
    dvec B_ext = dvec::Zero(size);
    for(llong k_ = 0; k_ < ke.size(); k_++) { B_ext += B.col(ke[k_]); }
    for(llong k_ = 0; k_ < kf.size(); k_++) { B_fix += B.col(kf[k_]); }

    double T_ext = 0;
    double T_fix = 0;
    double T_ext_var = 0;
    double T_fix_var = 0;

    dvec E_ext = dvec::Zero(size);
    dvec E_fix = dvec::Zero(size);
    dvec E_uncond = dvec::Zero(size);

    for (llong i_ = 0; i_ < si.size(); i_++) {
        llong i = si[i_];
        for(llong o_ = 0; o_ < nnz_p0[i_]; o_++) {
            double o = p0[i_](o_);
            llong idx = i + o_;
            double iw = o * ConfigWfesSwitching::p[i_]; // integration weight

            E_uncond += iw * N_rows[idx];

            dvec E_ext_i = B_ext.array() * N_rows[idx].array() / B_ext[idx];
            dvec E_ext_var_i = B_ext.array() * N2_rows[idx].array() / B_ext[idx];
            T_ext += iw * E_ext_i.sum();
            T_ext_var += (2 * E_ext_var_i.sum() - E_ext_i.sum() - pow(E_ext_i.sum(), 2)) * iw;
            E_ext += iw * E_ext_i;

            dvec E_fix_i = B_fix.array() * N_rows[idx].array() / B_fix[idx];
            dvec E_fix_var_i = B_fix.array() * N2_rows[idx].array() / B_fix[idx];
            T_fix += iw * E_fix_i.sum();
            T_fix_var += (2 * E_fix_var_i.sum() - E_fix_i.sum() - pow(E_fix_i.sum(), 2)) * iw;
            E_fix += iw * E_fix_i;
        }
    }

    // time spent in each model conditional on absorbing in a particuar state
    dvec T_cond_fix = dvec::Zero(ConfigWfesSwitching::num_comp);
    dvec T_cond_ext = dvec::Zero(ConfigWfesSwitching::num_comp);
    dvec T_uncond   = dvec::Zero(ConfigWfesSwitching::num_comp);
    for(llong i_ = 0; i_ < si.size(); i_++){
        T_cond_ext[i_] = E_ext.segment(si[i_], (2 * ConfigWfesSwitching::N[i_]) - 1).sum();
        T_cond_fix[i_] = E_fix.segment(si[i_], (2 * ConfigWfesSwitching::N[i_]) - 1).sum();
        T_uncond[i_]   = E_uncond.segment(si[i_], (2 * ConfigWfesSwitching::N[i_]) - 1).sum();
    }

    double T_ext_std = sqrt(T_ext_var);
    double T_fix_std = sqrt(T_fix_var);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfesSwitching::output_N_Ext)
        utils::writeVectorToFile(E_ext, ConfigWfesSwitching::path_output_N_Ext);
    if (ConfigWfesSwitching::output_N_Fix)
        utils::writeVectorToFile(E_fix, ConfigWfesSwitching::path_output_N_Fix);
    if (ConfigWfesSwitching::output_N)
        utils::writeVectorMapToFile(N_rows, ConfigWfesSwitching::path_output_N);
    if (ConfigWfesSwitching::output_B) {
        utils::writeMatrixToFile(B, ConfigWfesSwitching::path_output_B);
    }
    delete solver;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    ResultsWfesSwitching* res = new ResultsWfesSwitching(P_ext, P_fix, T_ext, T_ext_std, T_fix, T_fix_std, P_cond_ext, P_cond_fix, T_uncond, T_cond_ext, T_cond_fix, dt.count());

    if(ConfigWfesSwitching::output_Res)
       res->writeResultsToFile(res, ConfigWfesSwitching::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

ResultsWfesSwitching *wfes_switching::fixation()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix W = wrightfisher::Switching(ConfigWfesSwitching::N, wrightfisher::FIXATION_ONLY, ConfigWfesSwitching::s, ConfigWfesSwitching::h, ConfigWfesSwitching::u, ConfigWfesSwitching::v, ConfigWfesSwitching::r, ConfigWfesSwitching::a, msg_level);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfesSwitching::output_Q)
        W.Q->saveMarket(ConfigWfesSwitching::path_output_Q);
    if (ConfigWfesSwitching::output_R)
        utils::writeMatrixToFile(W.R, ConfigWfesSwitching::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    W.Q->subtractIdentity();

    llong size = (2 * ConfigWfesSwitching::N.sum());
    dvec id(size);

    Solver* solver = SolverFactory::createSolver(ConfigWfesSwitching::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSwitching::vienna_solver);

    solver->preprocess();

    dmat N(ConfigWfesSwitching::num_comp, size);
    lvec start_state_index(ConfigWfesSwitching::num_comp);
    start_state_index(0) = 0;
    for(llong i = 1; i < ConfigWfesSwitching::num_comp; i++) {
        start_state_index(i) = (2 * ConfigWfesSwitching::N(i - 1)) + start_state_index(i - 1);
    }

    for(llong i = 0; i < ConfigWfesSwitching::num_comp; i++) {
        id.setZero();
        id(start_state_index(i)) = 1;
        N.row(i) = solver->solve(id, true);
        N.row(i) *= ConfigWfesSwitching::p(i);
    }

    double T_fix = N.sum();
    double rate = 1.0 / T_fix;

    dmat B(size, ConfigWfesSwitching::num_comp);

    for(llong i = 0; i < ConfigWfesSwitching::num_comp; i++) {
        dvec R_col = W.R.col(i);
        B.col(i) = solver->solve(R_col, false);
    }

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfesSwitching::output_N)
        utils::writeMatrixToFile(N, ConfigWfesSwitching::path_output_N);
    if (ConfigWfesSwitching::output_B) {
        utils::writeMatrixToFile(B, ConfigWfesSwitching::path_output_B);
    }
    delete solver;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    ResultsWfesSwitching* res = new ResultsWfesSwitching(T_fix, rate, dt.count());

    if(ConfigWfesSwitching::output_Res)
       res->writeResultsToFile(res, ConfigWfesSwitching::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

void wfes_switching::force() {
    if (!ConfigWfesSwitching::force) {
        if (ConfigWfesSwitching::N.maxCoeff() > 500000) {
            // TODO Show as dialog.
            throw exception::Error("Population size is quite large - the computations will take a long time. Use --force to ignore");
        }
        dvec N = ConfigWfesSwitching::N.cast<double>();
        dvec theta_f = dvec::Constant(ConfigWfesSwitching::num_comp, 4).array() * N.array() * ConfigWfesSwitching::v.array();
        dvec theta_b = dvec::Constant(ConfigWfesSwitching::num_comp, 4).array() * N.array() * ConfigWfesSwitching::u.array();
        double max_theta = std::max(theta_b.maxCoeff(), theta_f.maxCoeff());
        if (max_theta > 1) {
            // TODO Show as dialog.
            throw exception::Error("The mutation rate might violate the Wright-Fisher assumptions. Use --force to ignore");
        }
        dvec gamma = dvec::Constant(ConfigWfesSwitching::num_comp, 2).array() * N.array() * ConfigWfesSwitching::s.array();
        if (2 * N.maxCoeff() * ConfigWfesSwitching::s.minCoeff() <= -100) {
            // TODO Show as dialog.
            throw exception::Error("The selection coefficient is quite negative. Fixations might be impossible. Use --force to ignore");
        }
        if (ConfigWfesSwitching::a > 1e-5) {
            // TODO Show as dialog.
            throw exception::Error("Zero cutoff value is quite high. This might produce inaccurate results. Use --force to ignore");
        }
    }
}