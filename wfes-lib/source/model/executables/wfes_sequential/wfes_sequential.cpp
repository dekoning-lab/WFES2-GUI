#include "wfes_sequential.h"

using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSequential *wfes_sequential::execute()
{

    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigWfesSequential::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfesSequential::n_threads);
    mkl_set_num_threads(ConfigWfesSequential::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

        return this->function();
}

ResultsWfesSequential *wfes_sequential::function()
{

    if (!ConfigWfesSequential::force) {
        if (ConfigWfesSequential::N.maxCoeff() > 500000) {
            qDebug() << "Population size is quite large - the computations will take a long time. Use --force to ignore";
        }
        dvec N = ConfigWfesSequential::N.cast<double>();
        dvec theta_f = dvec::Constant(ConfigWfesSequential::num_comp, 4).array() * N.array() * ConfigWfesSequential::v.array();
        dvec theta_b = dvec::Constant(ConfigWfesSequential::num_comp, 4).array() * N.array() * ConfigWfesSequential::u.array();
        double max_theta = std::max(theta_b.maxCoeff(), theta_f.maxCoeff());
        if (max_theta > 1) {
            qDebug() << "The mutation rate might violate the Wright-Fisher assumptions. Use --force to ignore";
        }
        dvec gamma = dvec::Constant(ConfigWfesSequential::num_comp, 2).array() * N.array() * ConfigWfesSequential::s.array();
        if (2 * N.maxCoeff() * ConfigWfesSequential::s.minCoeff() <= -100) {
            qDebug() << "The selection coefficient is quite negative. Fixations might be impossible. Use --force to ignore";
        }
        if (ConfigWfesSequential::a > 1e-5) {
            qDebug() << "Zero cutoff value is quite high. This might produce inaccurate results. Use --force to ignore";
        }
    }
    //}}}

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

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
            ConfigWfesSequential::s, ConfigWfesSequential::h, ConfigWfesSequential::u, ConfigWfesSequential::v, switching, ConfigWfesSequential::a, msg_level);

    W.R.conservativeResize(W.R.rows(), W.R.cols() + 1);
    W.R.col(W.R.cols() - 1) = Z;

    // SI are start indeces - a vector of size n_models
    lvec si = startIndeces(2 * ConfigWfesSequential::N - lvec::Ones(ConfigWfesSequential::num_comp));

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfesSequential::output_Q)
        W.Q->saveMarket(ConfigWfesSequential::path_output_Q);
    if (ConfigWfesSequential::output_R)
        utils::writeMatrixToFile(W.R, ConfigWfesSequential::path_output_R);

    W.Q->subtractIdentity();

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    Solver* solver = SolverFactory::createSolver(ConfigWfesSequential::library, *(W.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSequential::vienna_solver);

    solver->preprocess();

    // Get initial probabilities of mu within each model
    lvec nnz_p0(ConfigWfesSequential::num_comp);
    std::vector<dvec> p0(ConfigWfesSequential::num_comp);
    for (llong i = 0; i < ConfigWfesSequential::num_comp; i++) {
        llong pop_size = ConfigWfesSequential::N(i);
        dvec first_row = wrightfisher::binom_row(2 * pop_size, wrightfisher::psi_diploid(0, pop_size, ConfigWfesSequential::s(i), ConfigWfesSequential::h(i), ConfigWfesSequential::u(i), ConfigWfesSequential::v(i)), ConfigWfesSequential::a).Q;
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

    // Output {{{
    if(ConfigWfesSequential::output_N_Ext)
        writeVectorToFile(E_ext, ConfigWfesSequential::path_output_N_Ext);
    if(ConfigWfesSequential::output_N_Fix)
        writeVectorToFile(E_fix, ConfigWfesSequential::path_output_N_Fix);
    if(ConfigWfesSequential::output_N_Tmo)
        writeVectorToFile(E_tmo, ConfigWfesSequential::path_output_N_Tmo);
    if(ConfigWfesSequential::output_N)
        writeVectorMapToFile(N_rows, ConfigWfesSequential::path_output_N);
    if(ConfigWfesSequential::output_B)
        writeMatrixToFile(B, ConfigWfesSequential::path_output_B);

    QImage *imageQ = nullptr, *imageR = nullptr,  *imageN = nullptr, *imageB = nullptr, *imageN_ext = nullptr, *imageN_fix = nullptr, *imageN_tmo = nullptr;
    if(ConfigWfesSequential::output_Q) {
        imageQ = utils::generateImage(W.Q->dense());
        //utils::saveImage(imageI, "Image_I");
        ImageResults::Q = imageQ;
    }
    if(ConfigWfesSequential::output_R) {
        imageR = utils::generateImage(W.R);
        //utils::saveImage(imageI, "Image_I");
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
        //utils::saveImage(imageN, "Image_N");
        ImageResults::N = imageN;
    }
    if(ConfigWfesSequential::output_B) {
        imageB = utils::generateImage(B);
        //utils::saveImage(imageB, "Image_B");
        ImageResults::B = imageB;
    }
    if(ConfigWfesSequential::output_N_Ext) {
        imageN_ext = utils::generateImage(E_ext);
        //utils::saveImage(imageB, "Image_B");
        ImageResults::N_ext = imageN_ext;
    }
    if(ConfigWfesSequential::output_N_Fix) {
        imageN_fix = utils::generateImage(E_fix);
        //utils::saveImage(imageB, "Image_B");
        ImageResults::N_fix = imageN_fix;
    }
    if(ConfigWfesSequential::output_N_Tmo) {
        imageN_tmo = utils::generateImage(E_tmo);
        //utils::saveImage(imageB, "Image_B");
        ImageResults::N_tmo = imageN_tmo;
    }

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    ResultsWfesSequential *res =  new ResultsWfesSequential(P_ext, P_fix, P_tmo, T_ext, T_ext_std, T_fix, T_fix_std, T_tmo, T_tmo_std, dt.count());

    if(ConfigWfesSequential::output_Res)
       res->writeResultsToFile(res, ConfigWfesSequential::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}
