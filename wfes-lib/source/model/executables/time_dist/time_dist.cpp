#include "time_dist.h"

using namespace wfes::wrightfisher;
using namespace wfes::utils;
using namespace wfes::config;
using namespace wfes;

ResultsTimeDist *time_dist::execute()
{
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigTimeDist::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    #ifdef OMP
        omp_set_num_threads(ConfigTimeDist::n_threads);
    #endif
        mkl_set_num_threads(ConfigTimeDist::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // All cases (models) are wrapped in this switch instruction.
    switch(ConfigTimeDist::modelType) {
        case ModelTypeTimeDist::TIME_DIST:
            return this->timeDist();
        case ModelTypeTimeDist::TIME_DIST_SGV:
            return this->timeDistSGV();
        case ModelTypeTimeDist::TIME_DIST_SKIP:
            return this->timeDistSkip();
        case ModelTypeTimeDist::TIME_DIST_DUAL:
            return this->timeDistDual();

        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypeTimeDist::NONE:
        default:
            // TODO Show error as dialog. Right now it does nothing.
            return new ResultsTimeDist();
    }
}

ResultsTimeDist *time_dist::timeDist()
{

    //Notify building matrix.
    this->notify(ExecutionStatus::BUILDING_MATRICES);

    wrightfisher::Matrix wf = wrightfisher::Single(ConfigTimeDist::population_size, ConfigTimeDist::population_size, wrightfisher::BOTH_ABSORBING, ConfigTimeDist::s, ConfigTimeDist::h, ConfigTimeDist::u, ConfigTimeDist::v,
                               ConfigTimeDist::rem, ConfigTimeDist::a, msg_level, ConfigTimeDist::b);

    //Notify saving data.
    this->notify(ExecutionStatus::SAVING_DATA);

    if (ConfigTimeDist::output_Q)
        wf.Q->saveMarket(ConfigTimeDist::path_output_Q);
    if (ConfigTimeDist::output_R)
        utils::writeMatrixToFile(wf.R, ConfigTimeDist::path_output_R);

    dmat PH(ConfigTimeDist::max_t, 5);

    dvec c = dvec::Zero(2 * ConfigTimeDist::population_size - 1);
    c(0) = 1;

    double cdf = 0;
    llong i;
    for (i = 0; cdf < ConfigTimeDist::integration_cutoff && i < ConfigTimeDist::max_t; i++) {

        double P_ext_t = wf.R.col(0).dot(c);
        double P_fix_t = wf.R.col(1).dot(c);
        cdf += P_fix_t + P_ext_t;

        PH(i, 0) = i + 1;
        PH(i, 1) = P_ext_t;
        PH(i, 2) = P_fix_t;
        PH(i, 3) = P_ext_t + P_fix_t;
        PH(i, 4) = cdf;

        c = wf.Q->multiply(c, true);
    }
    PH.conservativeResize(i, 5);

    if (ConfigTimeDist::output_P) {
        utils::writeMatrixToFile(PH, ConfigTimeDist::path_output_P);
    }

    if (ConfigTimeDist::verbose) {
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;
        std::cout << "Total runtime: " << dt.count() << " s" << std::endl;
    }

    //Calculate time.
    t_end = std::chrono::system_clock::now();
    time_diff dt = t_end - t_start;

    return new ResultsTimeDist(dt.count());

}

ResultsTimeDist *time_dist::timeDistSGV()
{

}

ResultsTimeDist *time_dist::timeDistSkip()
{

}

ResultsTimeDist *time_dist::timeDistDual()
{

}
