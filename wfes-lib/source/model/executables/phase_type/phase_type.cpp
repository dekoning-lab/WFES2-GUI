#include "phase_type.h"

using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsPhaseType *phase_type::execute()
{
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigPhaseType::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigPhaseType::n_threads);
    mkl_set_num_threads(ConfigPhaseType::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    switch(ConfigPhaseType::modelType) {
        case ModelTypePhaseType::PHASE_TYPE_DIST:
            return this->phaseTypeDist();
        case ModelTypePhaseType::PHASE_TYPE_MOMENTS:
            return this->phaseTypeMoment();
        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypePhaseType::NONE:
        default:
            // TODO Show error as dialog.
            return new ResultsPhaseType();
    }

}

ResultsPhaseType *phase_type::phaseTypeDist()
{
    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    dmat PH(ConfigPhaseType::max_t, 3);

    dvec c = dvec::Zero(2 * ConfigPhaseType::population_size);
    c(0) = 1;

    wrightfisher::Matrix wf = wrightfisher::Single(ConfigPhaseType::population_size, ConfigPhaseType::population_size, wrightfisher::FIXATION_ONLY, ConfigPhaseType::s, ConfigPhaseType::h, ConfigPhaseType::u, ConfigPhaseType::v, ConfigPhaseType::rem,
                               ConfigPhaseType::a, msg_level, ConfigPhaseType::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigPhaseType::output_Q)
        wf.Q->saveMarket(ConfigPhaseType::path_output_Q);
    if (ConfigPhaseType::output_R)
        utils::writeMatrixToFile(wf.R, ConfigPhaseType::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    dvec R = wf.R.col(0);

    double cdf = 0;
    llong i;
    for (i = 0; cdf < ConfigPhaseType::integration_cutoff && i < ConfigPhaseType::max_t; i++) {

        double P_abs_t = R.dot(c);
        cdf += P_abs_t;

        PH(i, 0) = i + 1;
        PH(i, 1) = P_abs_t;
        PH(i, 2) = cdf;

        c = wf.Q->multiply(c, true);
    }
    PH.conservativeResize(i, 3);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (ConfigPhaseType::output_P) {
        utils::writeMatrixToFile(PH, ConfigPhaseType::path_output_P);
    }

    QImage *imageQ = nullptr, *imageR = nullptr, *imageP = nullptr;
    if(ConfigPhaseType::output_Q) {
        imageQ = utils::generateImage(wf.Q->dense());
        //utils::saveImage(imageI, "Image_I");
        ImageResults::Q = imageQ;
    }
    if(ConfigPhaseType::output_R) {
        imageR = utils::generateImage(wf.R);
        //utils::saveImage(imageI, "Image_I");
        ImageResults::R = imageR;
    }
    if(ConfigPhaseType::output_P) {
        imageP = utils::generateImage(PH);
        //utils::saveImage(imageI, "Image_I");
        ImageResults::P = imageP;
    }

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    ResultsPhaseType* res = new ResultsPhaseType(dt.count());

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

ResultsPhaseType *phase_type::phaseTypeMoment()
{
    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix wf = wrightfisher::Single(ConfigPhaseType::population_size, ConfigPhaseType::population_size, wrightfisher::FIXATION_ONLY, ConfigPhaseType::s, ConfigPhaseType::h, ConfigPhaseType::u, ConfigPhaseType::v, true, ConfigPhaseType::a, msg_level, ConfigPhaseType::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigPhaseType::output_Q)
        wf.Q->saveMarket(ConfigPhaseType::path_output_Q);
    if (ConfigPhaseType::output_R)
        utils::writeMatrixToFile(wf.R, ConfigPhaseType::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    wf.Q->subtractIdentity();

    Solver* solver = SolverFactory::createSolver(ConfigPhaseType::library, *(wf.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigPhaseType::vienna_solver);

    try {
        solver->preprocess();
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsPhaseType(e.what());
    } catch(...) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsPhaseType("INTEL MKL PARDISO: Unknown error while preprocessing the matrix.");
    }

    dvec z = dvec::Zero(ConfigPhaseType::k+1);
    z(0) = 1; z(1) = -1;

    llong size = 2 * ConfigPhaseType::population_size;
    dvec rhs = dvec::Ones(size);
    dmat m = dmat::Zero(size, ConfigPhaseType::k+1);
    m.col(0) = rhs;
    try {
        m.col(1) = solver->solve(rhs, false);
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsPhaseType(e.what());
    } catch(...) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsPhaseType("INTEL MKL PARDISO: Unknown error while preprocessing the matrix.");
    }

    for(llong i = 1; i < ConfigPhaseType::k; i++) {
        z(i + 1) = -1;
        for (llong j = i; j > 0; j--) {
            z(j) = z(j - 1) - z(j);
        }
        z(0) = -z(0);
        rhs.setZero();
        for (llong j = 0; j < i+1; j++) {
            rhs += z(j) * m.col(j);
        }

        // note that we only need the first row of M - do we need to solve every time?
        try {
            m.col(i+1) = solver->solve(rhs, false);
        } catch(const std::exception &e) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsPhaseType(e.what());
        } catch(...) {
            this->notify(ExecutionStatus::ERROR);
            return new ResultsPhaseType("INTEL MKL PARDISO: Unknown error while preprocessing the matrix.");
        }
    }
    double m1 = m(0, 1);
    double m2 = m(0, 2);

    delete solver;

    QImage *imageQ = nullptr, *imageR = nullptr;
    if(ConfigPhaseType::output_Q) {
        imageQ = utils::generateImage(wf.Q->dense());
        //utils::saveImage(imageI, "Image_I");
        ImageResults::Q = imageQ;
    }
    if(ConfigPhaseType::output_R) {
        imageR = utils::generateImage(wf.R);
        //utils::saveImage(imageI, "Image_I");
        ImageResults::R = imageR;
    }

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    ResultsPhaseType* res = new ResultsPhaseType(m1, sqrt(m2 - (m1 * m1)), m.row(0), dt.count());

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Print moments.
    if(ConfigPhaseType::output_Moments)
        utils::writeVectorToFile(m.row(0), ConfigPhaseType::path_output_Moments);

    if(ConfigPhaseType::output_Res)
       res->writeResultsToFile(res, ConfigPhaseType::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}
