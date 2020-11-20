#include "wfafle.h"

using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfafle *wfafle::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfafle::n_threads);
    mkl_set_num_threads(ConfigWfafle::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Start execution.
    return this->function();

}

ResultsWfafle *wfafle::function() {
    try{
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        llong k = ConfigWfafle::N.size();

        std::deque<dvec> d;
        dvec initial;
        if (ConfigWfafle::initial_distribution_csv.compare("") != 0) {
            initial = load_csv_col_vector(ConfigWfafle::initial_distribution_csv);
        } else if (ConfigWfafle::p != 0) {
            llong p = ConfigWfafle::p;
            initial = dvec::Zero(2 * ConfigWfafle::N(0) + 1);
            initial[p] = 1;
        } else {
            initial = wrightfisher::Equilibrium(ConfigWfafle::N(0), ConfigWfafle::s(0), ConfigWfafle::h(0), ConfigWfafle::u(0), ConfigWfafle::v(0), ConfigWfafle::a, msg_level);
        }
        d.push_back(initial);

        for(llong i = 0; i < k - 1; i++) {
            iterate_generations(d[i], ConfigWfafle::N(i), ConfigWfafle::G(i), ConfigWfafle::s(i), ConfigWfafle::h(i), ConfigWfafle::u(i), ConfigWfafle::v(i), ConfigWfafle::a, msg_level);
            d.push_back(switch_population_size(d[i], ConfigWfafle::N(i), ConfigWfafle::N(i + 1), ConfigWfafle::s(i + 1), ConfigWfafle::h(i + 1), ConfigWfafle::u(i + 1), ConfigWfafle::v(i + 1), ConfigWfafle::a));
        }

        iterate_generations(d[k - 1], ConfigWfafle::N(k - 1), ConfigWfafle::G(k - 1), ConfigWfafle::ConfigWfafle::s(k - 1), ConfigWfafle::h(k - 1), ConfigWfafle::u(k - 1), ConfigWfafle::v(k - 1), ConfigWfafle::a, msg_level);

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if(ConfigWfafle::output_Dist) {
            utils::writeVectorToFile(d[k - 1], ConfigWfafle::path_output_Dist);
        }
        // write_vector_to_file(d[k - 1], "stdout");
        std::cout << d[k - 1] << std::endl;

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsWfafle(d[k-1], dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfafle(e.what());
    }
}

void wfafle::iterate_generations(dvec &x, llong N, llong t, double s, double h, double u, double v, double alpha, bool verbose) {
    wrightfisher::Matrix wf = wrightfisher::Single(N, N, wrightfisher::NON_ABSORBING, s, h, u, v, true, alpha, verbose);
    wf.Q->multiplyInPlaceRep(x, t, true);
    x /= x.sum();
}

dvec wfafle::switch_population_size(dvec &x, llong Nx, llong Ny, double s, double h, double u, double v, double alpha, bool verbose) {
    wrightfisher::Matrix wf = wrightfisher::Single(Nx, Ny, wrightfisher::NON_ABSORBING, s, h, u, v, true, alpha, verbose);
    dvec next = wf.Q->multiply(x, true);
    next /= next.sum();
    return next;
}
