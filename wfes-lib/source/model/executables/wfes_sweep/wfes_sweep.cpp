#include "wfes_sweep.h"

using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSweep *wfes_sweep::execute()
{
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigWfesSweep::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfesSweep::n_threads);
    mkl_set_num_threads(ConfigWfesSweep::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    this->calculateStartingCopies();

    // Save initial distribution if resquested by the user.
    if (ConfigWfesSweep::output_I)
        utils::writeVectorToFile(starting_copies_p, ConfigWfesSweep::path_output_I);

    this->calculateZ();

    switch(ConfigWfesSweep::modelType) {
        case ModelTypeWfesSweep::FIXATION:
            return this->fixation();
        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypeWfesSweep::NONE:
        default:
            // TODO Show error as dialog.
            return new ResultsWfesSweep();
    }

}

ResultsWfesSweep *wfes_sweep::fixation()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    dmat switching(2, 2); switching << 1 - ConfigWfesSweep::l, ConfigWfesSweep::l, 0, 1;

    wrightfisher::Matrix wf = wrightfisher::NonAbsorbingToFixationOnly(ConfigWfesSweep::population_size, ConfigWfesSweep::s, ConfigWfesSweep::h, ConfigWfesSweep::u, ConfigWfesSweep::v, switching, ConfigWfesSweep::a, msg_level, ConfigWfesSweep::b, ConfigWfesSweep::library);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    if (ConfigWfesSweep::output_Q)
        wf.Q->saveMarket(ConfigWfesSweep::path_output_Q);
    if (ConfigWfesSweep::output_R)
        utils::writeMatrixToFile(wf.R, ConfigWfesSweep::path_output_R);

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    wf.Q->subtractIdentity();

    Solver* solver = SolverFactory::createSolver(ConfigWfesSweep::library, *(wf.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSweep::vienna_solver);

    try {
        solver->preprocess();
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSweep(e.what());
    } catch(...) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSweep("INTEL MKL PARDISO: Unknown error while preprocessing the matrix.");
    }

    dvec id(wf.Q->num_rows);
    id.setZero();
    id(ConfigWfesSweep::starting_copies) = 1;

    dvec N(wf.Q->num_rows);
    try {
        N = solver->solve(id, true);
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSweep(e.what());
    } catch(...) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSweep("INTEL MKL PARDISO: Unknown error while solving the system.");
    }
    double T_fix = N.tail(2 * ConfigWfesSweep::population_size).sum();
    qDebug() << "Fixation";
    double rate = 1.0 / T_fix;

    llong size = ((2 * ConfigWfesSweep::population_size) + 1) + (2 * ConfigWfesSweep::population_size);

    dvec R_ext = wf.R.col(0);
    dvec B_ext;
    try {
        B_ext = solver->solve(R_ext, false);
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSweep(e.what());
    } catch(...) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfesSweep("INTEL MKL PARDISO: Unknown error while solving the system.");
    }
    dvec B_fix = dvec::Ones(size) - B_ext;

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    //Save data into file.
    dmat B(size, 2);
    if (ConfigWfesSweep::output_N)
        utils::writeMatrixToFile(N, ConfigWfesSweep::path_output_N);
    if (ConfigWfesSweep::output_B) {
        B.col(0) = B_ext;
        B.col(1) = B_fix;
        utils::writeMatrixToFile(B, ConfigWfesSweep::path_output_B);
    }
    delete solver;

    QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr,  *imageN = nullptr, *imageB = nullptr;
    if(ConfigWfesSweep::output_I) {
        imageI = utils::generateImage(starting_copies_p);
        //utils::saveImage(imageI, "Image_I");
        ImageResults::I = imageI;
    }
    if(ConfigWfesSweep::output_Q) {
        imageQ = utils::generateImage(wf.Q->dense());
        //utils::saveImage(imageI, "Image_I");
        ImageResults::Q = imageQ;
    }
    if(ConfigWfesSweep::output_R) {
        imageR = utils::generateImage(wf.R);
        //utils::saveImage(imageI, "Image_I");
        ImageResults::R = imageR;
    }
    if(ConfigWfesSweep::output_N) {
        imageN = utils::generateImage(N);
        //utils::saveImage(imageN, "Image_N");
        ImageResults::N = imageN;
    }
    if(ConfigWfesSweep::output_B) {
        imageB = utils::generateImage(B);
        //utils::saveImage(imageB, "Image_B");
        ImageResults::B = imageB;
    }

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    ResultsWfesSweep* res = new ResultsWfesSweep(T_fix, rate, dt.count());

    if(ConfigWfesSweep::output_Res)
       res->writeResultsToFile(res, ConfigWfesSweep::path_output_Res);

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return res;
}

void wfes_sweep::calculateStartingCopies()
{
    ConfigWfesSweep s;
    dvec first_row = wrightfisher::binom_row(2 * ConfigWfesSweep::population_size, wrightfisher::psi_diploid(0, ConfigWfesSweep::population_size, ConfigWfesSweep::s(0), ConfigWfesSweep::h(0), ConfigWfesSweep::u(0), ConfigWfesSweep::v(0)), ConfigWfesSweep::a).Q;
    starting_copies_p = first_row.tail(first_row.size() - 1); // renormalize
    starting_copies_p /= 1 - first_row(0);
}

void wfes_sweep::calculateZ()
{
    z = 0;

    if(ConfigWfesSweep::integration_cutoff <= 0) { // no integration
        z = 1;
        starting_copies_p[0] = 1;
    } else {
        for(llong i = 0; starting_copies_p(i) > ConfigWfesSweep::integration_cutoff; i++, z++);
    }
    if(ConfigWfesSweep::starting_copies != 0) z = 1;


}
