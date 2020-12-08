#include "time_dist.h"

using namespace wfes::controllers;
using namespace wfes::wrightfisher;
using namespace wfes::utils;
using namespace wfes::config;
using namespace wfes;

ResultsTimeDist *time_dist::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    // Since it is a GUI application, always quiet for a better performance.
    msg_level = MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigTimeDist::n_threads);
    mkl_set_num_threads(ConfigTimeDist::n_threads);

    // Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Select the mode from configuration.
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
            return new ResultsTimeDist();
    }
}

ResultsTimeDist *time_dist::timeDist() {
    try {

        // Population-scaled values.
        double s = ConfigTimeDist::s;
        double u = ConfigTimeDist::u;
        double v = ConfigTimeDist::v;
        if(GlobalConfiguration::populationScaled) {
            s = ConfigTimeDist::s / (2 * ConfigTimeDist::population_size);
            u = ConfigTimeDist::u / (4 * ConfigTimeDist::population_size);
            v = ConfigTimeDist::v / (4 * ConfigTimeDist::population_size);
        }

        // This is for chart visualization.
        QList<QPointF> ext;
        QList<QPointF> fix;
        QList<QPointF> abs;
        QList<QPointF> acum;
        double minExt = std::numeric_limits<double>::max();
        double maxExt = std::numeric_limits<double>::min();
        double minFix = std::numeric_limits<double>::max();
        double maxFix = std::numeric_limits<double>::min();
        double minAbs = std::numeric_limits<double>::max();
        double maxAbs = std::numeric_limits<double>::min();
        double minAcum = std::numeric_limits<double>::max();
        double maxAcum = std::numeric_limits<double>::min();
        // This is for chart visualization.

        // Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix wf = wrightfisher::Single(ConfigTimeDist::population_size, ConfigTimeDist::population_size, wrightfisher::BOTH_ABSORBING, s, ConfigTimeDist::h, u, v,
                                   ConfigTimeDist::rem, ConfigTimeDist::a, msg_level, ConfigTimeDist::b);

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_Q)
            wf.Q->saveMarket(ConfigTimeDist::path_output_Q);
        if (ConfigTimeDist::output_R)
            utils::writeMatrixToFile(wf.R, ConfigTimeDist::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

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

            // This is for chart visualization.
            ext.append(QPointF(i + 1, P_ext_t));
            fix.append(QPointF(i + 1, P_fix_t));
            abs.append(QPointF(i + 1, P_ext_t + P_fix_t));
            acum.append(QPointF(i + 1, cdf));
            if(minExt >= P_ext_t)
                minExt = P_ext_t;
            if(maxExt <= P_ext_t)
                maxExt = P_ext_t;
            if(minFix >= P_fix_t)
                minFix = P_fix_t;
            if(maxFix <= P_fix_t)
                maxFix = P_fix_t;
            if(minAbs >= P_ext_t + P_fix_t)
                minAbs = P_ext_t + P_fix_t;
            if(maxAbs <= P_ext_t + P_fix_t)
                maxAbs = P_ext_t + P_fix_t;
            if(minAcum >= cdf)
                minAcum = cdf;
            if(maxAcum <= cdf)
                maxAcum = cdf;
            // This is for chart visualization.

        }
        PH.conservativeResize(i, 5);

        // This is for chart visualization.
        ChartResults::timeDistExt = ext;
        ChartResults::timeDistFix = fix;
        ChartResults::timeDistAbs = abs;
        ChartResults::timeDistAcum = acum;
        ChartResults::minMaxTimeDistExt = QPointF(minExt, maxExt);
        ChartResults::minMaxTimeDistFix = QPointF(minFix, maxFix);
        ChartResults::minMaxTimeDistAbs = QPointF(minAbs, maxAbs);
        ChartResults::minMaxTimeDistAcum = QPointF(minAcum, maxAcum);
        // This is for chart visualization.

        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_P) {
            utils::writeMatrixToFile(PH, ConfigTimeDist::path_output_P);
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr, *imageP = nullptr;
            if(ConfigTimeDist::output_Q) {
                imageQ = utils::generateImage(wf.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigTimeDist::output_R) {
                imageR = utils::generateImage(wf.R);
                ImageResults::R = imageR;
            }
            if(ConfigTimeDist::output_P) {
                imageP = utils::generateImage(PH);
                ImageResults::P = imageP;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsTimeDist(PH, dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsTimeDist(e.what());
    }

}

ResultsTimeDist *time_dist::timeDistSGV() {
    try {
        // Population-scaled values.
        dvec s = ConfigTimeDistSGV::s;
        dvec u = ConfigTimeDistSGV::u;
        dvec v = ConfigTimeDistSGV::v;
        if(GlobalConfiguration::populationScaled) {
            s = ConfigTimeDistSGV::s / (2 * ConfigTimeDistSGV::population_size);
            u = ConfigTimeDistSGV::u / (4 * ConfigTimeDistSGV::population_size);
            v = ConfigTimeDistSGV::v / (4 * ConfigTimeDistSGV::population_size);
        }

        // This is for chart visualization.
        QList<QPointF> subs;
        QList<QPointF> acum;
        double minSubs = std::numeric_limits<double>::max();
        double maxSubs = std::numeric_limits<double>::min();
        double minAcum = std::numeric_limits<double>::max();
        double maxAcum = std::numeric_limits<double>::min();
        // This is for chart visualization.

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        dmat switching(2, 2); switching << 1 - ConfigTimeDistSGV::l, ConfigTimeDistSGV::l, 0, 1;

        wrightfisher::Matrix wf = wrightfisher::NonAbsorbingToFixationOnly(ConfigTimeDistSGV::population_size, s, ConfigTimeDistSGV::h, u, v, switching, ConfigTimeDistSGV::a, msg_level, ConfigTimeDist::b);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_Q)
            wf.Q->saveMarket(ConfigTimeDist::path_output_Q);
        if (ConfigTimeDist::output_R)
            utils::writeMatrixToFile(wf.R, ConfigTimeDist::path_output_R);

        // Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        dmat PH(ConfigTimeDistSGV::max_t, 3);

        dvec c = dvec::Zero(4 * ConfigTimeDistSGV::population_size + 1);
        c(0) = 1;
        dvec R = wf.R.col(0);

        double cdf = 0;
        llong i;
        for (i = 0; cdf < ConfigTimeDistSGV::integration_cutoff && i < ConfigTimeDistSGV::max_t; i++) {

            double P_abs_t = R.dot(c);
            cdf += P_abs_t;

            PH(i, 0) = i + 1;
            PH(i, 1) = P_abs_t;
            PH(i, 2) = cdf;

            c = wf.Q->multiply(c, true);

            // This is for chart visualization.
            subs.append(QPointF(i + 1, P_abs_t));
            acum.append(QPointF(i + 1, cdf));
            if(minSubs >= P_abs_t)
                minSubs = P_abs_t;
            if(maxSubs <= P_abs_t)
                maxSubs = P_abs_t;
            if(minAcum >= cdf)
                minAcum = cdf;
            if(maxAcum <= cdf)
                maxAcum = cdf;
            // This is for chart visualization.
        }
        PH.conservativeResize(i, 3);

        // This is for chart visualization.
        ChartResults::timeDistSGVSub = subs;
        ChartResults::timeDistSGVAcum = acum;
        ChartResults::minMaxTimeDistSGVSub = QPointF(minSubs, maxSubs);
        ChartResults::minMaxTimeDistSGVAcum = QPointF(minAcum, maxAcum);
        // This is for chart visualization.


        // Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_P) {
            utils::writeMatrixToFile(PH, ConfigTimeDist::path_output_P);
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr, *imageP = nullptr;
            if(ConfigTimeDist::output_Q) {
                imageQ = utils::generateImage(wf.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigTimeDist::output_R) {
                imageR = utils::generateImage(wf.R);
                ImageResults::R = imageR;
            }
            if(ConfigTimeDist::output_P) {
                imageP = utils::generateImage(PH);
                ImageResults::P = imageP;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsTimeDist(PH, dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsTimeDist(e.what());
    }
}


ResultsTimeDist *time_dist::timeDistSkip() {
    try {
        // Population-scaled values.
        double s = ConfigTimeDist::s;
        double u = ConfigTimeDist::u;
        double v = ConfigTimeDist::v;
        if(GlobalConfiguration::populationScaled) {
            s = ConfigTimeDist::s / (2 * ConfigTimeDist::population_size);
            u = ConfigTimeDist::u / (4 * ConfigTimeDist::population_size);
            v = ConfigTimeDist::v / (4 * ConfigTimeDist::population_size);
        }

        // This is for chart visualization.
        QList<QPointF> subs;
        QList<QPointF> acum;
        double minSubs = std::numeric_limits<double>::max();
        double maxSubs = std::numeric_limits<double>::min();
        double minAcum = std::numeric_limits<double>::max();
        double maxAcum = std::numeric_limits<double>::min();
        // This is for chart visualization.

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix wf = wrightfisher::Bounce(ConfigTimeDist::population_size, ConfigTimeDist::population_size,
                                                       s, ConfigTimeDist::h, u, v,
                                                       ConfigTimeDist::rem, ConfigTimeDist::a, msg_level, ConfigTimeDist::b);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_Q)
            wf.Q->saveMarket(ConfigTimeDist::path_output_Q);
        if (ConfigTimeDist::output_R)
            utils::writeMatrixToFile(wf.R, ConfigTimeDist::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        dmat PH(ConfigTimeDist::max_t, 3);
        dvec c = dvec::Zero(2 * ConfigTimeDist::population_size - 1);
        c(0) = 1;

        double cdf = 0;

        llong i;

        for (i = 0; cdf < ConfigTimeDist::integration_cutoff && i < ConfigTimeDist::max_t; i++) {

            double P_abs_t = wf.R.col(0).dot(c);
            cdf += P_abs_t;

            PH(i, 0) = i + 1;
            PH(i, 1) = P_abs_t;
            PH(i, 2) = cdf;
            c = wf.Q->multiply(c, true);

            // This is for chart visualization.
            subs.append(QPointF(i + 1, P_abs_t));
            acum.append(QPointF(i + 1, cdf));
            if(minSubs >= P_abs_t)
                minSubs = P_abs_t;
            if(maxSubs <= P_abs_t)
                maxSubs = P_abs_t;
            if(minAcum >= cdf)
                minAcum = cdf;
            if(maxAcum <= cdf)
                maxAcum = cdf;
            // This is for chart visualization.
        }
        PH.conservativeResize(i, 3);

        // This is for chart visualization.
        ChartResults::timeDistSkipSub = subs;
        ChartResults::timeDistSkipAcum = acum;
        ChartResults::minMaxTimeDistSkipSub = QPointF(minSubs, maxSubs);
        ChartResults::minMaxTimeDistSkipAcum = QPointF(minAcum, maxAcum);
        // This is for chart visualization.

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_P) {
            utils::writeMatrixToFile(PH, ConfigTimeDist::path_output_P);
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr, *imageP = nullptr;
            if(ConfigTimeDist::output_Q) {
                imageQ = utils::generateImage(wf.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigTimeDist::output_R) {
                imageR = utils::generateImage(wf.R);
                ImageResults::R = imageR;
            }
            if(ConfigTimeDist::output_P) {
                imageP = utils::generateImage(PH);
                ImageResults::P = imageP;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsTimeDist(PH, dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsTimeDist(e.what());
    }
}

ResultsTimeDist *time_dist::timeDistDual() {
    try {
        // Population-scaled values.
        double s = ConfigTimeDist::s;
        double u = ConfigTimeDist::u;
        double v = ConfigTimeDist::v;
        if(GlobalConfiguration::populationScaled) {
            s = ConfigTimeDist::s / (2 * ConfigTimeDist::population_size);
            u = ConfigTimeDist::u / (4 * ConfigTimeDist::population_size);
            v = ConfigTimeDist::v / (4 * ConfigTimeDist::population_size);
        }

        // This is for chart visualization.
        QList<QPointF> ext;
        QList<QPointF> fix;
        QList<QPointF> abs;
        QList<QPointF> acum;
        double minExt = std::numeric_limits<double>::max();
        double maxExt = std::numeric_limits<double>::min();
        double minFix = std::numeric_limits<double>::max();
        double maxFix = std::numeric_limits<double>::min();
        double minAbs = std::numeric_limits<double>::max();
        double maxAbs = std::numeric_limits<double>::min();
        double minAcum = std::numeric_limits<double>::max();
        double maxAcum = std::numeric_limits<double>::min();
        // This is for chart visualization.

        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);

        wrightfisher::Matrix wf = wrightfisher::DualMutation(ConfigTimeDist::population_size, ConfigTimeDist::population_size, s, ConfigTimeDist::h, u, v, ConfigTimeDist::rem, ConfigTimeDist::a, msg_level, ConfigTimeDist::b);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_Q)
            wf.Q->saveMarket(ConfigTimeDist::path_output_Q);
        if (ConfigTimeDist::output_R)
            utils::writeMatrixToFile(wf.R, ConfigTimeDist::path_output_R);

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);

        dmat PH(ConfigTimeDist::max_t, 5);

        dvec c = dvec::Zero(2 * ConfigTimeDist::population_size);
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


            // This is for chart visualization.
            ext.append(QPointF(i + 1, P_ext_t));
            fix.append(QPointF(i + 1, P_fix_t));
            abs.append(QPointF(i + 1, P_ext_t + P_fix_t));
            acum.append(QPointF(i + 1, cdf));
            if(minExt >= P_ext_t)
                minExt = P_ext_t;
            if(maxExt <= P_ext_t)
                maxExt = P_ext_t;
            if(minFix >= P_fix_t)
                minFix = P_fix_t;
            if(maxFix <= P_fix_t)
                maxFix = P_fix_t;
            if(minAbs >= P_ext_t + P_fix_t)
                minAbs = P_ext_t + P_fix_t;
            if(maxAbs <= P_ext_t + P_fix_t)
                maxAbs = P_ext_t + P_fix_t;
            if(minAcum >= cdf)
                minAcum = cdf;
            if(maxAcum <= cdf)
                maxAcum = cdf;
            // This is for chart visualization.
        }
        PH.conservativeResize(i, 5);

        // This is for chart visualization.
        ChartResults::timeDistDualExt = ext;
        ChartResults::timeDistDualFix = fix;
        ChartResults::timeDistDualAbs = abs;
        ChartResults::timeDistDualAcum = acum;
        ChartResults::minMaxTimeDistDualExt = QPointF(minExt, maxExt);
        ChartResults::minMaxTimeDistDualFix = QPointF(minFix, maxFix);
        ChartResults::minMaxTimeDistDualAbs = QPointF(minAbs, maxAbs);
        ChartResults::minMaxTimeDistDualAcum = QPointF(minAcum, maxAcum);
        // This is for chart visualization.

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);

        // Save data into file.
        if (ConfigTimeDist::output_P) {
            utils::writeMatrixToFile(PH, ConfigTimeDist::path_output_P);
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageQ = nullptr, *imageR = nullptr, *imageP = nullptr;
            if(ConfigTimeDist::output_Q) {
                imageQ = utils::generateImage(wf.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigTimeDist::output_R) {
                imageR = utils::generateImage(wf.R);
                ImageResults::R = imageR;
            }
            if(ConfigTimeDist::output_P) {
                imageP = utils::generateImage(PH);
                ImageResults::P = imageP;
            }
        }

        //Calculate time.
        t_end = std::chrono::system_clock::now();
        time_diff dt = t_end - t_start;

        //Notify done.
        this->notify(ExecutionStatus::DONE);

        return new ResultsTimeDist(PH, dt.count());
    } catch(const std::exception &e) {
        this->notify(ExecutionStatus::ERROR);
        return new ResultsTimeDist(e.what());
    }
}
