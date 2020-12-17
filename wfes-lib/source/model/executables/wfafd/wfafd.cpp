#include "wfafd.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfafd *wfafd::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfafd::n_threads);
    mkl_set_num_threads(ConfigWfafd::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Start execution.
    return this->function();

}

ResultsWfafd *wfafd::function() {
    try{
        // Population-scaled values.
        dvec s = ConfigWfafd::s;
        dvec u = ConfigWfafd::u;
        dvec v = ConfigWfafd::v;
        if(GlobalConfiguration::populationScaled) {
            for (int i = 0; i < ConfigWfafd::num_comp; i++) {
                s[i] = ConfigWfafd::s[i] / (2.0 * ConfigWfafd::N[i]);
                u[i] = ConfigWfafd::u[i] / (4.0 * ConfigWfafd::N[i]);
                v[i] = ConfigWfafd::v[i] / (4.0 * ConfigWfafd::N[i]);
            }
        }

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        llong k = ConfigWfafd::N.size();

        std::deque<dvec> d;
        dvec initial;
        if (ConfigWfafd::initial_distribution_csv.compare("") != 0) {
            initial = load_csv_col_vector(ConfigWfafd::initial_distribution_csv);
            // Check if Initial Distribution File (i) size is correct.
            if(initial.size() != (2 * ConfigWfafd::N[0] + 1)) {
                this->notify(ExecutionStatus::ERROR);
                return new ResultsWfafd("Initial Probability Distribution (I) file must have " + std::to_string(2 * ConfigWfafd::N[0] + 1) + " elements. Your file has just " + std::to_string(initial.size()) + " elements.");
            }
        } else if (ConfigWfafd::p != 0) {
            llong p = ConfigWfafd::p;
            initial = dvec::Zero(2 * ConfigWfafd::N(0) + 1);
            initial[p] = 1;
        } else {
            initial = wrightfisher::Equilibrium(ConfigWfafd::N(0), s(0), ConfigWfafd::h(0), u(0), v(0), ConfigWfafd::a, msg_level);
        }
        d.push_back(initial);

        for(llong i = 0; i < k - 1; i++) {
            iterate_generations(d[i], ConfigWfafd::N(i), ConfigWfafd::G(i), s(i), ConfigWfafd::h(i), u(i), v(i), ConfigWfafd::a, msg_level);
            d.push_back(switch_population_size(d[i], ConfigWfafd::N(i), ConfigWfafd::N(i + 1), s(i + 1), ConfigWfafd::h(i + 1), u(i + 1), v(i + 1), ConfigWfafd::a));
        }

        iterate_generations(d[k - 1], ConfigWfafd::N(k - 1), ConfigWfafd::G(k - 1), s(k - 1), ConfigWfafd::h(k - 1), u(k - 1), v(k - 1), ConfigWfafd::a, msg_level);

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if(ConfigWfafd::output_Dist) {
            utils::writeVectorToFile(d[k - 1], ConfigWfafd::path_output_Dist);
        }
        // write_vector_to_file(d[k - 1], "stdout");
        std::cout << d[k - 1] << std::endl;


        // This is for chart visualization.
        QList<QPointF> dist;
        double minDist = std::numeric_limits<double>::max();
        double maxDist = std::numeric_limits<double>::min();
        for(int i = 0; i < d[k - 1].size(); i++) {
            if(minDist >= d[k - 1][i])
                minDist = d[k - 1][i];
            if(maxDist <= d[k - 1][i])
                maxDist = d[k - 1][i];
            dist.append(QPointF(i+1, d[k - 1][i]));
        }
        ChartResults::wfafdDist = dist;
        ChartResults::minMaxwfafdDist = QPointF(minDist, maxDist);
        // This is for chart visualization.

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsWfafd(d[k-1], dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsWfafd(e.what());
    }
}

void wfafd::iterate_generations(dvec &x, llong N, llong t, double s, double h, double u, double v, double alpha, bool verbose) {
    wrightfisher::Matrix wf = wrightfisher::Single(N, N, wrightfisher::NON_ABSORBING, s, h, u, v, true, alpha, verbose);
    wf.Q->multiplyInPlaceRep(x, t, true);
    x /= x.sum();
}

dvec wfafd::switch_population_size(dvec &x, llong Nx, llong Ny, double s, double h, double u, double v, double alpha, bool verbose) {
    wrightfisher::Matrix wf = wrightfisher::Single(Nx, Ny, wrightfisher::NON_ABSORBING, s, h, u, v, true, alpha, verbose);
    dvec next = wf.Q->multiply(x, true);
    next /= next.sum();
    return next;
}
