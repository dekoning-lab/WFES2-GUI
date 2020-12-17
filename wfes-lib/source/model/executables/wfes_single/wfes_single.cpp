#include "wfes_single.h"

using namespace wfes::controllers;
using namespace wfes::wrightfisher;
using namespace wfes::solver;
using namespace wfes::sparsematrix;
using namespace wfes::pardiso;
using namespace wfes::config;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSingle* wfes_single::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfesSingle::n_threads);
    mkl_set_num_threads(ConfigWfesSingle::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Population-scaled values.
    double s = ConfigWfesSingle::s;
    double u = ConfigWfesSingle::u;
    double v = ConfigWfesSingle::v;
    if(GlobalConfiguration::populationScaled) {
        s = ConfigWfesSingle::s / (2 * ConfigWfesSingle::population_size);
        u = ConfigWfesSingle::u / (4 * ConfigWfesSingle::population_size);
        v = ConfigWfesSingle::v / (4 * ConfigWfesSingle::population_size);
    }

    // Set value for starting copies if the user has provided an initial distribution,
    // load it and calculate starting copies p.
    this->calculateStartingCopies(s, u, v);

    // Save initial distribution if resquested by the user.
    if (ConfigWfesSingle::output_I)
        utils::writeVectorToFile(starting_copies_p, ConfigWfesSingle::path_output_I);

    // Set value of z if the user has provided an initial distribution,
    // load it and calculate z value.
    this->calculateZ(v);

    // Select the mode from configuration.
    switch(ConfigWfesSingle::modelType) {
        case ModelTypeWfesSingle::ABSORPTION:
            return this->absorption(s, u, v);
        case ModelTypeWfesSingle::FIXATION:
            return this->fixation(s, u, v);
        case ModelTypeWfesSingle::FUNDAMENTAL:
            return this->fundamental(s, u, v);
        case ModelTypeWfesSingle::EQUILIBRIUM:
            return this->equilibrium(s, u, v);
        case ModelTypeWfesSingle::ESTABLISHMENT:
            return this->establishment(s, u, v);
        case ModelTypeWfesSingle::ALLELE_AGE:
            return this->alleleAge(s, u, v);
        case ModelTypeWfesSingle::NON_ABSORBING:
            return this->nonAbsorbing(s, u, v);
        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypeWfesSingle::NONE:
        default:
            return new ResultsWfesSingle();
    }
}

ResultsWfesSingle *wfes_single::absorption(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix W = wrightfisher::Single(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, wrightfisher::BOTH_ABSORBING, s, ConfigWfesSingle::h, u, v,
                                  ConfigWfesSingle::rem, ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfesSingle::output_Q)
            W.Q->saveMarket(ConfigWfesSingle::path_output_Q);
        if (ConfigWfesSingle::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSingle::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        W.Q->subtractIdentity();

        llong size = (2 * ConfigWfesSingle::population_size) - 1;

        if(ConfigWfesSingle::initial_distribution_csv.compare("") != 0 && starting_copies_p.size() != size) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsWfesSingle("Initial Probability Distribution (I) file must have " + std::to_string(size) + " elements. Your file has just " + std::to_string(starting_copies_p.size()) + " elements.");
        }

        Solver* solver = SolverFactory::createSolver(ConfigWfesSingle::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

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
        if (!ConfigWfesSingle::starting_copies) {
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
            id(ConfigWfesSingle::starting_copies) = 1;
            N_mat.row(0) = solver->solve(id, true);
            dvec N1 = N_mat.row(0);
            N2_mat.row(0) = solver->solve(N1, true);
            dvec N2 = N2_mat.row(0);

            T_abs = N1.sum();
            T_abs_var = (2 * N2.sum() - N1.sum()) - pow(N1.sum(), 2);

            P_ext = B_ext(ConfigWfesSingle::starting_copies);
            dvec E_ext = B_ext.array() * N1.array() / B_ext(ConfigWfesSingle::starting_copies);
            E_ext_mat.row(0) = E_ext;
            dvec E_ext_var = B_ext.array() * N2.array() / B_ext(ConfigWfesSingle::starting_copies);
            T_ext = E_ext.sum();
            T_ext_var = (2 * E_ext_var.sum() - E_ext.sum()) - pow(E_ext.sum(), 2);

            P_fix = B_fix(ConfigWfesSingle::starting_copies);
            dvec E_fix = B_fix.array() * N1.array() / B_fix(ConfigWfesSingle::starting_copies);
            E_fix_mat.row(0) = E_fix;
            dvec E_fix_var = B_fix.array() * N2.array() / B_fix(ConfigWfesSingle::starting_copies);
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

        N_ext /= (1 / (2 * ConfigWfesSingle::population_size * v)) + T_ext;

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        dmat B(size, 2);
        if (ConfigWfesSingle::output_N)
            utils::writeMatrixToFile(N_mat, ConfigWfesSingle::path_output_N);
        if (ConfigWfesSingle::output_N_ext)
            utils::writeMatrixToFile(E_ext_mat, ConfigWfesSingle::path_output_N_ext);
        if (ConfigWfesSingle::output_N_fix)
            utils::writeMatrixToFile(E_fix_mat, ConfigWfesSingle::path_output_N_fix);
        if (ConfigWfesSingle::output_B) {
            B.col(0) = B_ext;
            B.col(1) = B_fix;
            utils::writeMatrixToFile(B, ConfigWfesSingle::path_output_B);
        }

        delete solver;

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr, *imageN = nullptr, *imageNExt = nullptr, *imageNFix = nullptr, *imageB = nullptr;
            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSingle::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSingle::output_N) {
                imageN = utils::generateImage(N_mat);
                ImageResults::N = imageN;
            }
            if(ConfigWfesSingle::output_N_ext) {
                imageNExt = utils::generateImage(E_ext_mat);
                ImageResults::N_ext = imageNExt;
            }
            if(ConfigWfesSingle::output_N_fix) {
                imageNFix = utils::generateImage(E_fix_mat);
                ImageResults::N_fix = imageNFix;
            }
            if(ConfigWfesSingle::output_B) {
                B.col(0) = B_ext;
                B.col(1) = B_fix;
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSingle* res = new ResultsWfesSingle(ConfigWfesSingle::modelType, P_ext, P_fix, T_abs, T_abs_std, T_ext, T_ext_std, N_ext, T_fix, T_fix_std, dt.count());

        if(ConfigWfesSingle::output_Res)
           res->writeResultsToFile(res, ConfigWfesSingle::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }

}

ResultsWfesSingle *wfes_single::fixation(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix W = wrightfisher::Single(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, wrightfisher::FIXATION_ONLY, s, ConfigWfesSingle::h, u, v,
                                  ConfigWfesSingle::rem, ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        if (ConfigWfesSingle::output_Q)
            W.Q->saveMarket(ConfigWfesSingle::path_output_Q);
        if (ConfigWfesSingle::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSingle::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        W.Q->subtractIdentity();

        llong size = (2 * ConfigWfesSingle::population_size);

        if(ConfigWfesSingle::initial_distribution_csv.compare("") != 0 && starting_copies_p.size() != size) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsWfesSingle("Initial Probability Distribution (I) file must have " + std::to_string(size) + " elements. Your file has just " + std::to_string(starting_copies_p.size()) + " elements.");
        }

        Solver *solver = wfes::solver::SolverFactory::createSolver(ConfigWfesSingle::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

        solver->preprocess();

        dvec id(size);
        dmat N_mat(1, size);

        id.setZero();
        id(ConfigWfesSingle::starting_copies) = 1;

        N_mat.row(0) = solver->solve(id, true);

        dvec N1 = N_mat.row(0);
        dvec N2 = solver->solve(N1, true);

        double T_fix = N1.sum();
        double T_var = ((2 * N2.sum()) - N1.sum()) - pow(N1.sum(), 2);

        double rate = 1.0 / T_fix;
        double T_std = sqrt(T_var);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        dvec B = dvec::Ones(size);
        if (ConfigWfesSingle::output_N)
            utils::writeMatrixToFile(N_mat, ConfigWfesSingle::path_output_N);
        if (ConfigWfesSingle::output_B) {
            utils::writeVectorToFile(B, ConfigWfesSingle::path_output_B);
        }

        delete solver;

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr, *imageN = nullptr, *imageB = nullptr;

            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSingle::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSingle::output_N) {
                imageN = utils::generateImage(N_mat);
                ImageResults::N = imageN;
            }
            if(ConfigWfesSingle::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSingle* res = new ResultsWfesSingle(ConfigWfesSingle::modelType, T_fix, T_std, rate, dt.count());

        if(ConfigWfesSingle::output_Res)
           res->writeResultsToFile(res, ConfigWfesSingle::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }
}

ResultsWfesSingle *wfes_single::fundamental(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        llong size = (2 * ConfigWfesSingle::population_size) - 1;

        if(ConfigWfesSingle::initial_distribution_csv.compare("") != 0 && starting_copies_p.size() != size) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsWfesSingle("Initial Probability Distribution (I) file must have " + std::to_string(size) + " elements. Your file has just " + std::to_string(starting_copies_p.size()) + " elements.");
        }

        wrightfisher::Matrix W = wrightfisher::Single(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, wrightfisher::BOTH_ABSORBING, s, ConfigWfesSingle::h, u, v,
                                  ConfigWfesSingle::rem, ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        if (ConfigWfesSingle::output_Q)
            W.Q->saveMarket(ConfigWfesSingle::path_output_Q);
        if (ConfigWfesSingle::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSingle::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        W.Q->subtractIdentity();

        Solver* solver = SolverFactory::createSolver(ConfigWfesSingle::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

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

        //Save data into file.
        dmat V;
        if (ConfigWfesSingle::output_N)
            utils::writeMatrixToFile(N, ConfigWfesSingle::path_output_N);
        if (ConfigWfesSingle::output_V) {
            dvec Ndg = (2 * N.diagonal().array()) - 1;
            dmat Nsq = N.array().square();
            V = (N * diagmat(Ndg)) - Nsq;

            utils::writeMatrixToFile(V, ConfigWfesSingle::path_output_V);
        }
        delete solver;

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr, *imageN = nullptr, *imageV = nullptr;
            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSingle::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSingle::output_N) {
                imageN = utils::generateImage(N);
                ImageResults::N = imageN;
            }
            if(ConfigWfesSingle::output_V) {
                dvec Ndg = (2 * N.diagonal().array()) - 1;
                dmat Nsq = N.array().square();
                V = (N * diagmat(Ndg)) - Nsq;
                imageV = utils::generateImage(V);
                ImageResults::V = imageV;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsWfesSingle(ConfigWfesSingle::modelType, dt.count());

    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }
}

ResultsWfesSingle *wfes_single::equilibrium(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        llong size = (2 * ConfigWfesSingle::population_size) + 1;

        if(ConfigWfesSingle::initial_distribution_csv.compare("") != 0 && starting_copies_p.size() != size) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsWfesSingle("Initial Probability Distribution (I) file must have " + std::to_string(size) + " elements. Your file has just " + std::to_string(starting_copies_p.size()) + " elements.");
        }

        wrightfisher::Matrix W = wrightfisher::EquilibriumSolvingMatrix(ConfigWfesSingle::population_size, s, ConfigWfesSingle::h, u, v,
                                                                        ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);
        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        Solver* solver = SolverFactory::createSolver(ConfigWfesSingle::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

        solver->preprocess();

        dvec O = dvec::Zero(size);
        O(size - 1) = 1;
        dvec pi = solver->solve(O, true);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfesSingle::output_E) {
            utils::writeVectorToFile(pi, ConfigWfesSingle::path_output_E);
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

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageE = nullptr;
            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_E) {
                imageE = utils::generateImage(pi);
                ImageResults::E = imageE;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSingle* res = new ResultsWfesSingle(ConfigWfesSingle::modelType, e_freq, (1.0 - e_freq), dt.count());

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        if(ConfigWfesSingle::output_Res)
           res->writeResultsToFile(res, ConfigWfesSingle::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }
}

ResultsWfesSingle *wfes_single::establishment(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        // Full Wright-Fisher
        wrightfisher::Matrix W_full = wrightfisher::Single(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, wrightfisher::BOTH_ABSORBING, s, ConfigWfesSingle::h,
                                       u, v, ConfigWfesSingle::rem, ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        W_full.Q->subtractIdentity();

        llong size = (2 * ConfigWfesSingle::population_size) - 1;

        if(ConfigWfesSingle::initial_distribution_csv.compare("") != 0 && starting_copies_p.size() != size) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsWfesSingle("Initial Probability Distribution (I) file must have " + std::to_string(size) + " elements. Your file has just " + std::to_string(starting_copies_p.size()) + " elements.");
        }

        Solver* solver_full = SolverFactory::createSolver(ConfigWfesSingle::library, *(W_full.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

        solver_full->preprocess();
        dvec R_full_fix = W_full.R.col(1);
        dvec B_full_fix = solver_full->solve(R_full_fix, false);

        dvec B_full_ext = dvec::Constant(size, 1) - B_full_fix;
        dvec id_full(size);

        // establishment
        llong est_idx = 0;
        // find closest to k / (1 + k)
        // cout << odds_ratio / (1 + odds_ratio) << endl;
        dvec B_est_closest = B_full_fix - dvec::Constant(size, ConfigWfesSingle::odds_ratio / (1 + ConfigWfesSingle::odds_ratio));
        B_est_closest.array().abs().minCoeff(&est_idx);

        // TODO show as error in GUI
        if (est_idx == 1) {
            throw wfes::exception::Error("Establishment is near-certain: establishment-count is 1");
        }
        if (z >= est_idx) {
            throw wfes::exception::Error("Value of z is too high. Establishment can be reached by mutation alone");
        }

        // Since the B indexes begin at 1
        est_idx++;
        // cout << est_idx << endl;
        double est_freq = (double)(est_idx) / (2 * ConfigWfesSingle::population_size);

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
        wrightfisher::Matrix W_tr = wrightfisher::Truncated(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, est_idx, s, ConfigWfesSingle::h, u, v, ConfigWfesSingle::rem,
                                        ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfesSingle::output_Q)
            W_tr.Q->saveMarket(ConfigWfesSingle::path_output_Q);
        if (ConfigWfesSingle::output_R)
            utils::writeMatrixToFile(W_tr.R, ConfigWfesSingle::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        // To test
        // cout << W_tr.R.col(0) + W_tr.Q.dense().rowwise().sum() + W_tr.R.col(1) << endl;
        // cout << W.Q.dense() << endl;

        W_tr.Q->subtractIdentity();

        Solver* solver_tr = SolverFactory::createSolver(ConfigWfesSingle::library, *(W_tr.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

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
        if (!ConfigWfesSingle::starting_copies) {
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
            id(ConfigWfesSingle::starting_copies) = 1;
            N_mat.row(0) = solver_tr->solve(id, true);
            dvec N1 = N_mat.row(0);
            N2_mat.row(0) = solver_tr->solve(N1, true);
            dvec N2 = N2_mat.row(0);

            P_ext = B_ext(ConfigWfesSingle::starting_copies);
            dvec E_ext = B_ext.array() * N1.array() / B_ext(ConfigWfesSingle::starting_copies);
            E_ext_mat.row(0) = E_ext;
            dvec E_ext_var = B_ext.array() * N2.array() / B_ext(ConfigWfesSingle::starting_copies);
            T_ext = E_ext.sum();
            T_ext_var = (2 * E_ext_var.sum() - E_ext.sum()) - pow(E_ext.sum(), 2);

            P_est = B_est(ConfigWfesSingle::starting_copies);
            dvec E_est = B_est.array() * N1.array() / B_est(ConfigWfesSingle::starting_copies);
            E_est_mat.row(0) = E_est;
            dvec E_est_var = B_est.array() * N2.array() / B_est(ConfigWfesSingle::starting_copies);
            T_est = E_est.sum();
            T_est_var = (2 * E_est_var.sum() - E_est.sum()) - pow(E_est.sum(), 2);
        }
        double T_est_std = sqrt(T_est_var);

        delete solver_full;
        delete solver_tr;

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr;
            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_Q) {
                imageQ = utils::generateImage(W_tr.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSingle::output_R) {
                imageR = utils::generateImage(W_tr.R);
                ImageResults::R = imageR;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSingle* res = new ResultsWfesSingle(ConfigWfesSingle::modelType, est_freq, P_est, T_seg, T_seg_std,
                                   T_seg_ext, T_seg_ext_std, T_seg_fix, T_seg_fix_std, T_est, T_est_std, dt.count());

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        if(ConfigWfesSingle::output_Res)
           res->writeResultsToFile(res, ConfigWfesSingle::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }
}

ResultsWfesSingle *wfes_single::alleleAge(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        // Checking minimum and maximum value of observed copies in view, so it has been deleted here to avoid that an exception may crash the application.

        llong x = ConfigWfesSingle::observed_copies - 1;

        llong size = (2 * ConfigWfesSingle::population_size) - 1;

        if(ConfigWfesSingle::initial_distribution_csv.compare("") != 0 && starting_copies_p.size() != size) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsWfesSingle("Initial Probability Distribution (I) file must have " + std::to_string(size) + " elements. Your file has just " + std::to_string(starting_copies_p.size()) + " elements.");
        }

        wrightfisher::Matrix W = wrightfisher::Single(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, wrightfisher::BOTH_ABSORBING, s, ConfigWfesSingle::h, u, v,
                                  ConfigWfesSingle::rem, ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        if (ConfigWfesSingle::output_Q)
            W.Q->saveMarket(ConfigWfesSingle::path_output_Q);
        if (ConfigWfesSingle::output_R)
            utils::writeMatrixToFile(W.R, ConfigWfesSingle::path_output_R);
        dvec Q_x = W.Q-> getColCopy(x);
        W.Q->subtractIdentity();

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        Solver* solver = SolverFactory::createSolver(ConfigWfesSingle::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSingle::vienna_solver);

        solver->preprocess();

        W.Q->subtractIdentity();
        dvec Q_I_x = W.Q->getColCopy(x);
        Q_I_x(x) += 1;
        dvec A_x = W.Q->multiply(Q_I_x);

        double E_allele_age = 0;
        double S_allele_age = 0;
        if (!ConfigWfesSingle::starting_copies) {
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
            e_p(ConfigWfesSingle::starting_copies) = 1;

            dvec M1 = solver->solve(e_p, true);
            dvec M2 = solver->solve(M1, true);

            E_allele_age = M2.dot(Q_x) / M1(x);

            dvec M3 = solver->solve(M2, true);

            S_allele_age = sqrt((M3.dot(A_x) / M1(x)) - pow(E_allele_age, 2));
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr;
            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSingle::output_R) {
                imageR = utils::generateImage(W.R);
                ImageResults::R = imageR;
            }
        }

        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsWfesSingle* res = new ResultsWfesSingle(ConfigWfesSingle::modelType, E_allele_age, S_allele_age, true, dt.count());

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        if(ConfigWfesSingle::output_Res)
           res->writeResultsToFile(res, ConfigWfesSingle::path_output_Res);

        delete solver;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;

    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }
}

ResultsWfesSingle *wfes_single::nonAbsorbing(double s, double u, double v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix W = wrightfisher::Single(ConfigWfesSingle::population_size, ConfigWfesSingle::population_size, wrightfisher::NON_ABSORBING, s, ConfigWfesSingle::h, u, v,
                                  ConfigWfesSingle::rem, ConfigWfesSingle::a, msg_level, ConfigWfesSingle::b, ConfigWfesSingle::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        //Save data into file.
        if (ConfigWfesSingle::output_Q)
            W.Q->saveMarket(ConfigWfesSingle::path_output_Q);

        if(GlobalConfiguration::generateImages) {
            // Generate images from matrices and save to file.
            QImage *imageI = nullptr, *imageQ = nullptr;
            if(ConfigWfesSingle::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSingle::output_Q) {
                imageQ = utils::generateImage(W.Q->dense());
                ImageResults::Q = imageQ;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsWfesSingle(ConfigWfesSingle::modelType, true, dt.count());

    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSingle(e.what());
    }
}

void wfes_single::calculateStartingCopies(double s, double u, double v) {
    if (ConfigWfesSingle::initial_distribution_csv.compare("") != 0) {
        starting_copies_p = load_csv_col_vector(ConfigWfesSingle::initial_distribution_csv);
    } else {
        dvec first_row = wrightfisher::binom_row(2 * ConfigWfesSingle::population_size, wrightfisher::psi_diploid(0, ConfigWfesSingle::population_size, s, ConfigWfesSingle::h, u, v), ConfigWfesSingle::a).Q;
        starting_copies_p = first_row.tail(first_row.size() - 1); // renormalize
        starting_copies_p /= 1 - first_row(0);
    }
}

void wfes_single::calculateZ(double v) {
    // Set value of z if the user has provided an initial distribution,
    // load it and calculate z value.
    z = 0;
    if (ConfigWfesSingle::initial_distribution_csv.compare("") != 0) {
        z = starting_copies_p.size();
    } else if (ConfigWfesSingle::integration_cutoff <= 0 || v == 0) { // no integration
        z = 1;
        starting_copies_p[0] = 1;
    } else {
        int i = 0;
        while(i < starting_copies_p.size()) {
            if(starting_copies_p(i) > ConfigWfesSingle::integration_cutoff)
                z++;
            else break;
            i++;
        }
    }
    if (ConfigWfesSingle::starting_copies)
        z = 1;
}
