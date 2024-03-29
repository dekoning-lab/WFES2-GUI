#include "phase_type.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsPhaseType *phase_type::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigPhaseType::n_threads);
    mkl_set_num_threads(ConfigPhaseType::n_threads);

    // Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Select the mode from configuration.
    switch(ConfigPhaseType::modelType) {
        case ModelTypePhaseType::PHASE_TYPE_DIST:
            return this->phaseTypeDist();
        case ModelTypePhaseType::PHASE_TYPE_MOMENTS:
            return this->phaseTypeMoment();
        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypePhaseType::NONE:
        default:
            return new ResultsPhaseType();
    }

}

ResultsPhaseType *phase_type::phaseTypeDist() {
    try {
        // This is for chart visualization.
        QList<QPointF> dist;
        QList<QPointF> acum;
        double minDist = std::numeric_limits<double>::max();
        double maxDist = std::numeric_limits<double>::min();
        double minAcum = std::numeric_limits<double>::max();
        double maxAcum = std::numeric_limits<double>::min();
        // This is for chart visualization.

        // Population-scaled values.
        double s = ConfigPhaseType::s;
        double h = ConfigPhaseType::h;
        double u = ConfigPhaseType::u;
        double v = ConfigPhaseType::v;
        if(GlobalConfiguration::populationScaled) {
            s = ConfigPhaseType::s / (2 * ConfigPhaseType::population_size);
            h = ConfigPhaseType::h / (2 * ConfigPhaseType::population_size);
            u = ConfigPhaseType::u / (4 * ConfigPhaseType::population_size);
            v = ConfigPhaseType::v / (4 * ConfigPhaseType::population_size);
        }

        // Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }

        dmat PH(ConfigPhaseType::max_t, 3);
        dvec c = dvec::Zero(2 * ConfigPhaseType::population_size);
        c(0) = 1;

        wrightfisher::Matrix wf = wrightfisher::Single(ConfigPhaseType::population_size, ConfigPhaseType::population_size, wrightfisher::FIXATION_ONLY,
                                                       s, h, u, v,
                                                       ConfigPhaseType::rem, ConfigPhaseType::a, msg_level, ConfigPhaseType::b);

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }

        // Save data into file.
        if (ConfigPhaseType::output_Q)
            utils::writeSparseMatrixToFile(wf.Q, ConfigPhaseType::path_output_Q, "Phase-Type-Dist");
        if (ConfigPhaseType::output_R)
            utils::writeMatrixToFile(wf.R, ConfigPhaseType::path_output_R, "Phase-Type-Dist");

        // Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }

        dvec R = wf.R.col(0);
        double cdf = 0;
        llong i;

        for (i = 0; cdf < ConfigPhaseType::integration_cutoff && i < ConfigPhaseType::max_t; i++) {
            if(QThread::currentThread()->isInterruptionRequested()) {
                this->notify(ExecutionStatus::ABORTED);
                return new ResultsPhaseType();
            }

            double P_abs_t = R.dot(c);
            cdf += P_abs_t;

            PH(i, 0) = i + 1;
            PH(i, 1) = P_abs_t;
            PH(i, 2) = cdf;

            c = wf.Q->multiply(c, true);

            // This is for chart visualization.
            if(i % ConfigPhaseType::samplingFrequency == 0) {
                if(minDist >= P_abs_t)
                    minDist = P_abs_t;
                if(maxDist <= P_abs_t)
                    maxDist = P_abs_t;
                if(minAcum >= cdf)
                    minAcum = cdf;
                if(maxAcum <= cdf)
                    maxAcum = cdf;
                dist.append(QPointF(i+1, P_abs_t));
                acum.append(QPointF(i+1, cdf));
            }
            // This is for chart visualization.
        }

        // This is for chart visualization.
        ChartResults::phaseTypeDist = dist;
        ChartResults::phaseTypeDistAcum = acum;
        ChartResults::minMaxPhaseTypeDist = QPointF(minDist, maxDist);
        ChartResults::minMaxPhaseTypeAcum = QPointF(minAcum, maxAcum);
        // This is for chart visualization.

        PH.conservativeResize(i, 3);

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }

        // Save data into file.
        if (ConfigPhaseType::output_P) {
            utils::writeMatrixToFile(PH, ConfigPhaseType::path_output_P, "Phase-Type-Dist");
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr, *imageP = nullptr;
            if(ConfigPhaseType::output_Q) {
                imageQ = utils::generateImage(wf.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigPhaseType::output_R) {
                imageR = utils::generateImage(wf.R);
                ImageResults::R = imageR;
            }
            if(ConfigPhaseType::output_P) {
                imageP = utils::generateImage(PH);
                ImageResults::P = imageP;
            }
        }

        // Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        // Generate results.
        ResultsPhaseType* res = new ResultsPhaseType(PH, dt.count());

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;

    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::EXECUTION_ERROR);
        return new ResultsPhaseType(e.what());
    }
}

ResultsPhaseType *phase_type::phaseTypeMoment() {
    try {

        // Population-scaled values.
        double s = ConfigPhaseType::s;
        double u = ConfigPhaseType::u;
        double v = ConfigPhaseType::v;
        if(GlobalConfiguration::populationScaled) {
            s = ConfigPhaseType::s / (2 * ConfigPhaseType::population_size);
            u = ConfigPhaseType::u / (4 * ConfigPhaseType::population_size);
            v = ConfigPhaseType::v / (4 * ConfigPhaseType::population_size);
        }

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }


        wrightfisher::Matrix wf = wrightfisher::Single(ConfigPhaseType::population_size, ConfigPhaseType::population_size, wrightfisher::FIXATION_ONLY,
                                                       s, ConfigPhaseType::h, u, v,
                                                       true, ConfigPhaseType::a, msg_level, ConfigPhaseType::b);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }


        //Save data into file.
        if (ConfigPhaseType::output_Q)
            utils::writeSparseMatrixToFile(wf.Q, ConfigPhaseType::path_output_Q, "Phase-Type-Moments");
        if (ConfigPhaseType::output_R)
            utils::writeMatrixToFile(wf.R, ConfigPhaseType::path_output_R, "Phase-Type-Moments");

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }


        wf.Q->subtractIdentity();
        Solver* solver = SolverFactory::createSolver(ConfigPhaseType::library, *(wf.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC,
                                                     msg_level,ConfigPhaseType::vienna_solver);

        solver->preprocess();

        dvec z = dvec::Zero(ConfigPhaseType::k+1);
        z(0) = 1; z(1) = -1;

        llong size = 2 * ConfigPhaseType::population_size;
        dvec rhs = dvec::Ones(size);
        dmat m = dmat::Zero(size, ConfigPhaseType::k+1);
        m.col(0) = rhs;
        m.col(1) = solver->solve(rhs, false);

        for(llong i = 1; i < ConfigPhaseType::k; i++) {
            if(QThread::currentThread()->isInterruptionRequested()) {
                this->notify(ExecutionStatus::ABORTED);
                return new ResultsPhaseType();
            }

            z(i + 1) = -1;
            for (llong j = i; j > 0; j--) {
                z(j) = z(j - 1) - z(j);
            }
            z(0) = -z(0);
            rhs.setZero();
            for (llong j = 0; j < i+1; j++) {
                rhs += z(j) * m.col(j);
            }

            // TODO Note that we only need the first row of M - do we need to solve every time?
            m.col(i+1) = solver->solve(rhs, false);
        }

        double m1 = m(0, 1);
        double m2 = m(0, 2);

        delete solver;

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsPhaseType();
        }

        // Save data into file.
        if(ConfigPhaseType::output_Moments)
            utils::writeVectorToFile(m.row(0), ConfigPhaseType::path_output_Moments, "Phase-Type-Moments");

        if(GlobalConfiguration::generateImages) {
            // Generate images.
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
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        ResultsPhaseType* res = new ResultsPhaseType(m1, sqrt(m2 - (m1 * m1)), m.row(0), dt.count());
        if(ConfigPhaseType::output_Res)
           res->writeResultsToFile(res, ConfigPhaseType::path_output_Res);

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return res;
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::EXECUTION_ERROR);
        return new ResultsPhaseType(e.what());
    }
}
