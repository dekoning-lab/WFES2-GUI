#include "wfes_switching.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSwitching *wfes_switching::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfesSwitching::n_threads);
    mkl_set_num_threads(ConfigWfesSwitching::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // dmat switching = GTR::Matrix(p, r);

    // switching.diagonal() = dvec::Zero(n_models);
    // switching /= switching.sum();
    r = ConfigWfesSwitching::r;
    dvec row_sums = ConfigWfesSwitching::r.rowwise().sum();
    for (llong i = 0; i < ConfigWfesSwitching::num_comp; i++) {
        for (llong j = 0; j < ConfigWfesSwitching::num_comp; j++) {
            r(i, j) /= row_sums(i);
        }
    }

    // Select the mode from configuration.
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

ResultsWfesSwitching *wfes_switching::absorption() {
    try {
        // Population-scaled values.
        dvec s = ConfigWfesSwitching::s;
        dvec u = ConfigWfesSwitching::u;
        dvec v = ConfigWfesSwitching::v;
        if(GlobalConfiguration::populationScaled) {
            for (int i = 0; i < ConfigWfesSwitching::num_comp; i++) {
                s[i] = ConfigWfesSwitching::s[i] / (2.0 * ConfigWfesSwitching::N[i]);
                u[i] = ConfigWfesSwitching::u[i] / (4.0 * ConfigWfesSwitching::N[i]);
                v[i] = ConfigWfesSwitching::v[i] / (4.0 * ConfigWfesSwitching::N[i]);
            }
        }

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix W = wrightfisher::Switching(ConfigWfesSwitching::N, wrightfisher::BOTH_ABSORBING,
                s, ConfigWfesSwitching::h, u, v, r, ConfigWfesSwitching::a, msg_level);

        // SI are start indeces - a vector of size n_models
        lvec si = startIndeces(2 * ConfigWfesSwitching::N - lvec::Ones(ConfigWfesSwitching::num_comp));

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfesSwitching::output_Q)
            utils::writeSparseMatrixToFile(W.Q, ConfigWfesSwitching::path_output_Q, "WFES-Switching");
        if (ConfigWfesSwitching::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSwitching::path_output_R, "Wfes-Switching");

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
            dvec first_row = wrightfisher::binom_row(2 * pop_size, wrightfisher::psi_diploid(0, pop_size, s(i), ConfigWfesSwitching::h(i), u(i), v(i)), ConfigWfesSwitching::a).Q;
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
            utils::writeVectorToFile(E_ext, ConfigWfesSwitching::path_output_N_Ext, "WFES-Switching");
        if (ConfigWfesSwitching::output_N_Fix)
            utils::writeVectorToFile(E_fix, ConfigWfesSwitching::path_output_N_Fix, "WFES-Switching");
        if (ConfigWfesSwitching::output_N)
            utils::writeVectorMapToFile(N_rows, ConfigWfesSwitching::path_output_N, "WFES-Switching");
        if (ConfigWfesSwitching::output_B) {
            utils::writeMatrixToFile(B, ConfigWfesSwitching::path_output_B, "WFES-Switching");
        }
        delete solver;

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr,  *imageN = nullptr, *imageB = nullptr, *imageN_ext = nullptr, *imageN_fix = nullptr;
            if(ConfigWfesSwitching::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSwitching::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSwitching::output_N) {
                dmat N(N_rows.size(), N_rows[0].size());
                int i = 0;
                for(auto const &item : N_rows) {
                    dvec v = item.second;
                    N.row(i) = v.transpose();
                    i++;
                }
                imageN = utils::generateImage(N);
                utils::saveImage(imageN, "Image_N");
                ImageResults::N = imageN;
            }
            if(ConfigWfesSwitching::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
            if(ConfigWfesSwitching::output_N_Ext) {
                imageN_ext = utils::generateImage(E_ext);
                ImageResults::N_ext = imageN_ext;
            }
            if(ConfigWfesSwitching::output_N_Fix) {
                imageN_fix = utils::generateImage(E_fix);
                ImageResults::N_fix = imageN_fix;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSwitching* res = new ResultsWfesSwitching(P_ext, P_fix, T_ext, T_ext_std, T_fix, T_fix_std, P_cond_ext, P_cond_fix, T_uncond, T_cond_ext, T_cond_fix, dt.count());

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if(ConfigWfesSwitching::output_Res)
           res->writeResultsToFile(res, ConfigWfesSwitching::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSwitching(e.what());
    }
}

ResultsWfesSwitching *wfes_switching::fixation() {
    try {
        // Population-scaled values.
        dvec s = ConfigWfesSwitching::s;
        dvec u = ConfigWfesSwitching::u;
        dvec v = ConfigWfesSwitching::v;
        if(GlobalConfiguration::populationScaled) {
            for (int i = 0; i < ConfigWfesSwitching::num_comp; i++) {
                s[i] = ConfigWfesSwitching::s[i] / (2.0 * ConfigWfesSwitching::N[i]);
                u[i] = ConfigWfesSwitching::u[i] / (4.0 * ConfigWfesSwitching::N[i]);
                v[i] = ConfigWfesSwitching::v[i] / (4.0 * ConfigWfesSwitching::N[i]);
            }
        }

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix W = wrightfisher::Switching(ConfigWfesSwitching::N, wrightfisher::FIXATION_ONLY, s, ConfigWfesSwitching::h, u, v, r, ConfigWfesSwitching::a, msg_level);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfesSwitching::output_Q)
            utils::writeSparseMatrixToFile(W.Q, ConfigWfesSwitching::path_output_Q, "WFES-Switching");
        if (ConfigWfesSwitching::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSwitching::path_output_R, "WFES-Switching");

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
            utils::writeMatrixToFile(N, ConfigWfesSwitching::path_output_N, "WFES-Switching");
        if (ConfigWfesSwitching::output_B) {
            utils::writeMatrixToFile(B, ConfigWfesSwitching::path_output_B, "WFES-Switching");
        }
        delete solver;

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr,  *imageN = nullptr, *imageB = nullptr;
            if(ConfigWfesSwitching::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSwitching::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSwitching::output_N) {
                imageN = utils::generateImage(N);
                ImageResults::N = imageN;
            }
            if(ConfigWfesSwitching::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSwitching* res = new ResultsWfesSwitching(T_fix, rate, dt.count());

        if(ConfigWfesSwitching::output_Res)
           res->writeResultsToFile(res, ConfigWfesSwitching::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSwitching(e.what());
    }
}
