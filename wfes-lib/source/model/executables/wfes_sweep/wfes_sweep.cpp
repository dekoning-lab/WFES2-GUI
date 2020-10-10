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
    #ifdef OMP
        omp_set_num_threads(ConfigWfesSweep::n_threads);
    #endif
        mkl_set_num_threads(ConfigWfesSweep::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    this->force();

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

    //Notify solving
    this->notify(ExecutionStatus::SOLVING_MATRICES);

    wf.Q->subtractIdentity();

    Solver* solver = SolverFactory::createSolver(ConfigWfesSweep::library, *(wf.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSweep::vienna_solver);

    solver->preprocess();

    dvec id(wf.Q->num_rows);
    id.setZero();
    id(ConfigWfesSweep::starting_copies) = 1;

    dvec N(wf.Q->num_rows);
    N = solver->solve(id, true);

    double T_fix = N.tail(2 * ConfigWfesSweep::population_size).sum();
    qDebug() << "Fixation";
    double rate = 1.0 / T_fix;

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (ConfigWfesSweep::output_N)
        utils::writeMatrixToFile(N, ConfigWfesSweep::path_output_N);

    delete solver;

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    //Notify done.
    this->notify(ExecutionStatus::DONE);

    return new ResultsWfesSweep(T_fix, rate, dt.count());
}

void wfes_sweep::force()
{

    if(ConfigWfesSweep::s.size() != 2)  throw exception::Error("Selection coefficient vector should be of length 2");

    if (!ConfigWfesSweep::force) {
        if (ConfigWfesSweep::population_size > 500000) {
            // TODO Show as dialog.
            throw exception::Error("Population size is quite large - the computations will take a long "
                              "time. Use --force to ignore");
        }
        double max_mu = std::max(ConfigWfesSweep::u.maxCoeff(), ConfigWfesSweep::v.maxCoeff());
        if (4 * ConfigWfesSweep::population_size * max_mu > 1) {
            // TODO Show as dialog.
            throw exception::Error("The mutation rate might violate the Wright-Fisher assumptions. Use "
                              "--force to ignore");
        }
        if (ConfigWfesSweep::s.minCoeff() <= -1) {
            // TODO Show as dialog.
            throw exception::Error("The selection coefficient is quite negative. Fixations might be impossible. Use --force to ignore");
        }
        if (ConfigWfesSweep::a > 1e-5) {
            // TODO Show as dialog.
            throw exception::Error("Zero cutoff value is quite high. This might produce inaccurate results. Use --force to ignore");
        }
    }

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
