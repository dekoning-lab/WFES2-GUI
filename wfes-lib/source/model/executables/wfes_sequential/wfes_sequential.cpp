#include "wfes_sequential.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSequential *wfes_sequential::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfesSequential::n_threads);
    mkl_set_num_threads(ConfigWfesSequential::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Start execution.
    return this->function();
}

ResultsWfesSequential *wfes_sequential::function() {
    try {
        // Population-scaled values.
        dvec s = ConfigWfesSequential::s;
        dvec u = ConfigWfesSequential::u;
        dvec v = ConfigWfesSequential::v;
        if(GlobalConfiguration::populationScaled) {
            for (int i = 0; i < ConfigWfesSequential::num_comp; i++) {
                s[i] = ConfigWfesSequential::s[i] / (2.0 * ConfigWfesSequential::N[i]);
                u[i] = ConfigWfesSequential::u[i] / (4.0 * ConfigWfesSequential::N[i]);
                v[i] = ConfigWfesSequential::v[i] / (4.0 * ConfigWfesSequential::N[i]);
            }
        }

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSequential();
        }

        // Main calculation {{{
        llong size = (2 * ConfigWfesSequential::N.sum()) - ConfigWfesSequential::num_comp;

        dmat switching = dmat::Zero(ConfigWfesSequential::num_comp, ConfigWfesSequential::num_comp);
        for(llong i = 0; i < ConfigWfesSequential::num_comp - 1; i++) {
            switching(i, i) = 1 - (1 / ConfigWfesSequential::t(i));
            switching(i, i+1) = 1 / ConfigWfesSequential::t(i);
        }
        switching(ConfigWfesSequential::num_comp - 1, ConfigWfesSequential::num_comp - 1) = 1 - (1 / ConfigWfesSequential::t(ConfigWfesSequential::num_comp - 1));
        dvec Z = dvec::Zero(size);
        // [0 0 0 0 ... 1/t ... 2N_k-1 times ... 1/t 1/t]
        llong last_size = 2 * ConfigWfesSequential::N(ConfigWfesSequential::num_comp - 1) - 1;
        Z.tail(last_size) = dvec::Constant(last_size, 1 / (ConfigWfesSequential::t(ConfigWfesSequential::num_comp - 1)));

        wrightfisher::Matrix W = wrightfisher::Switching(ConfigWfesSequential::N, wrightfisher::BOTH_ABSORBING,
                s, ConfigWfesSequential::h, u, v, switching, ConfigWfesSequential::a, msg_level);

        W.R.conservativeResize(W.R.rows(), W.R.cols() + 1);
        W.R.col(W.R.cols() - 1) = Z;

        // SI are start indeces - a vector of size n_models
        lvec si = startIndeces(2 * ConfigWfesSequential::N - lvec::Ones(ConfigWfesSequential::num_comp));

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSequential();
        }

        //Save data into file.
        if (ConfigWfesSequential::output_Q)
            utils::writeSparseMatrixToFile(W.Q, ConfigWfesSequential::path_output_Q, "WFES-Sequential");
        if (ConfigWfesSequential::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSequential::path_output_R, "WFES-Sequential");

        W.Q->subtractIdentity();

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSequential();
        }

        Solver* solver = SolverFactory::createSolver(ConfigWfesSequential::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSequential::vienna_solver);

        solver->preprocess();
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSequential();
        }

        // Get initial probabilities of mu within each model
        lvec nnz_p0(ConfigWfesSequential::num_comp);
        std::vector<dvec> p0(ConfigWfesSequential::num_comp);
        for (llong i = 0; i < ConfigWfesSequential::num_comp; i++) {
            llong pop_size = ConfigWfesSequential::N(i);
            dvec first_row = wrightfisher::binom_row(2 * pop_size, wrightfisher::psi_diploid(0, pop_size, s(i), ConfigWfesSequential::h(i), u(i), v(i)), ConfigWfesSequential::a).Q;
            p0[i] = first_row.tail(first_row.size() - 1) / (1 - first_row(0)); // renormalize
            nnz_p0[i] = (p0[i].array() > ConfigWfesSequential::c).count();
        }

        // extinction and fixation column for each submodel plus timeout
        dmat B(size, (ConfigWfesSequential::num_comp * 2) + 1);
        for (llong i = 0; i < (ConfigWfesSequential::num_comp * 2) + 1; i++) {
            dvec R_col = W.R.col(i);
            B.col(i) = solver->solve(R_col, false);
        }

        std::map<llong, dvec> N_rows;
        std::map<llong, dvec> N2_rows;
        dvec id(size);
        for (llong i_ = 0; i_ < si.size(); i_++) {
            llong i = si[i_];
            for(llong o_ = 0; o_ < nnz_p0[i_]; o_++) {
                if(QThread::currentThread()->isInterruptionRequested()) {
                    this->notify(ExecutionStatus::ABORTED);
                    return new ResultsWfesSequential();
                }
                llong idx = i + o_;
                id.setZero();
                id(idx) = 1;
                N_rows[idx] = solver->solve(id, true);
                N2_rows[idx] = solver->solve(N_rows[idx], true);
            }
        }

        // absorbing extinction columns of B
        lvec ke = rangeStep(0, 2*ConfigWfesSequential::num_comp, 2);
        // absorbing fixation columns of B
        lvec kf = rangeStep(1, 2*ConfigWfesSequential::num_comp, 2);

        // Summarize extinction and fixation absorption vectors
        dvec B_fix = dvec::Zero(size);
        dvec B_ext = dvec::Zero(size);
        for(llong k_ = 0; k_ < ke.size(); k_++) { B_ext += B.col(ke[k_]); }
        for(llong k_ = 0; k_ < kf.size(); k_++) { B_fix += B.col(kf[k_]); }
        dvec B_tmo = B.col(B.cols() - 1);

        double P_ext = 0, P_fix = 0, P_tmo = 0;
        double T_ext = 0, T_fix = 0, T_tmo = 0;
        double T_ext_var = 0, T_fix_var = 0, T_tmo_var = 0;

        dvec E_ext = dvec::Zero(size);
        dvec E_fix = dvec::Zero(size);
        dvec E_tmo = dvec::Zero(size);

        // It doesn't make a lot of sense to integrate over all starting states, since the sequential model should have p= 1,0,0 by definition
        for (llong i_ = 0; i_ < si.size(); i_++) {
            llong i = si[i_];
            for(llong o_ = 0; o_ < nnz_p0[i_]; o_++) {
                if(QThread::currentThread()->isInterruptionRequested()) {
                    this->notify(ExecutionStatus::ABORTED);
                    return new ResultsWfesSequential();
                }
                double o = p0[i_](o_);
                llong idx = i + o_;
                double iw = o * ConfigWfesSequential::p[i_]; //integration_weight

                P_ext += B_ext[idx] * o * ConfigWfesSequential::p[i_];
                P_fix += B_fix[idx] * o * ConfigWfesSequential::p[i_];
                P_tmo += B_tmo[idx] * o * ConfigWfesSequential::p[i_];

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

                dvec E_tmo_i = B_tmo.array() * N_rows[idx].array() / B_tmo[idx];
                dvec E_tmo_var_i = B_tmo.array() * N2_rows[idx].array() / B_tmo[idx];
                T_tmo += iw * E_tmo_i.sum();
                T_tmo_var += (2 * E_tmo_var_i.sum() - E_tmo_i.sum() - pow(E_tmo_i.sum(), 2)) * iw;
                E_tmo += iw * E_tmo_i;
            }
        }


        double T_ext_std = sqrt(T_ext_var);
        double T_fix_std = sqrt(T_fix_var);
        double T_tmo_std = sqrt(T_tmo_var);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSequential();
        }

        // Save data into file.
        if(ConfigWfesSequential::output_N_Ext)
            writeVectorToFile(E_ext, ConfigWfesSequential::path_output_N_Ext, "WFES-Sequential");
        if(ConfigWfesSequential::output_N_Fix)
            writeVectorToFile(E_fix, ConfigWfesSequential::path_output_N_Fix, "WFES-Sequential");
        if(ConfigWfesSequential::output_N_Tmo)
            writeVectorToFile(E_tmo, ConfigWfesSequential::path_output_N_Tmo, "WFES-Sequential");
        if(ConfigWfesSequential::output_N)
            writeVectorMapToFile(N_rows, ConfigWfesSequential::path_output_N, "WFES-Sequential");
        if(ConfigWfesSequential::output_B)
            writeMatrixToFile(B, ConfigWfesSequential::path_output_B, "WFES-Sequential");

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr,  *imageN = nullptr, *imageB = nullptr, *imageN_ext = nullptr, *imageN_fix = nullptr, *imageN_tmo = nullptr;
            if(ConfigWfesSequential::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSequential::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSequential::output_N) {
                dmat N(N_rows.size(), N_rows[0].size());
                int i = 0;
                for(auto const &item : N_rows) {
                    dvec v = item.second;
                    N.row(i) = v.transpose();
                    i++;
                }
                imageN = utils::generateImage(N);
                ImageResults::N = imageN;
            }
            if(ConfigWfesSequential::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
            if(ConfigWfesSequential::output_N_Ext) {
                imageN_ext = utils::generateImage(E_ext);
                ImageResults::N_ext = imageN_ext;
            }
            if(ConfigWfesSequential::output_N_Fix) {
                imageN_fix = utils::generateImage(E_fix);
                ImageResults::N_fix = imageN_fix;
            }
            if(ConfigWfesSequential::output_N_Tmo) {
                imageN_tmo = utils::generateImage(E_tmo);
                ImageResults::N_tmo = imageN_tmo;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSequential *res =  new ResultsWfesSequential(P_ext, P_fix, P_tmo, T_ext, T_ext_std, T_fix, T_fix_std, T_tmo, T_tmo_std, dt.count());

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSequential();
        }

        // Save data into file.
        if(ConfigWfesSequential::output_Res)
           res->writeResultsToFile(res, ConfigWfesSequential::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::EXECUTION_ERROR);
        return new ResultsWfesSequential(e.what());
    }
}
