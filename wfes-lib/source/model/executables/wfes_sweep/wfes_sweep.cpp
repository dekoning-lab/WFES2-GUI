#include "wfes_sweep.h"

using namespace wfes::controllers;
using namespace wfes::config;
using namespace wfes::solver;
using namespace wfes::utils;
using namespace wfes;

ResultsWfesSweep *wfes_sweep::execute() {
    // Start counting execution time.
    t_start = std::chrono::system_clock::now();

    // Select verbose level for Intel MKL Pardiso.
    msg_level = ConfigWfesSweep::verbose ? MKL_PARDISO_MSG_VERBOSE : MKL_PARDISO_MSG_QUIET;

    // Set number of threads for intel MKL Pardiso.
    omp_set_num_threads(ConfigWfesSweep::n_threads);
    mkl_set_num_threads(ConfigWfesSweep::n_threads);

    //Notify starting.
    this->notify(ExecutionStatus::STARTING);

    // Population-scaled values.
    dvec s = ConfigWfesSweep::s;
    dvec u = ConfigWfesSweep::u;
    dvec v = ConfigWfesSweep::v;
    if(GlobalConfiguration::populationScaled) {
        for (int i = 0; i < ConfigWfesSweep::num_comp; i++) {
            s[i] = ConfigWfesSweep::s[i] / (2.0 * ConfigWfesSweep::population_size);
            u[i] = ConfigWfesSweep::u[i] / (4.0 * ConfigWfesSweep::population_size);
            v[i] = ConfigWfesSweep::v[i] / (4.0 * ConfigWfesSweep::population_size);
        }
    }

    // Set value for starting copies if the user has provided an initial distribution,
    // load it and calculate starting copies p.
    this->calculateStartingCopies(s, u, v);

    // Save initial distribution if resquested by the user.
    if (ConfigWfesSweep::output_I)
        utils::writeVectorToFile(starting_copies_p, ConfigWfesSweep::path_output_I, "WFES-Sweep");

    // Set value of z if the user has provided an initial distribution,
    // load it and calculate z value.
    this->calculateZ();

    // Select the mode from configuration.
    switch(ConfigWfesSweep::modelType) {
        case ModelTypeWfesSweep::FIXATION:
            return this->fixation(s, u, v);
        // If for some reason there is an error and the selected model type is none, or any of the previous one,
        // return default results, which is formed by nan values, so the GUI does not show anything.
        case ModelTypeWfesSweep::NONE:
        default:
            // TODO Show error as dialog.
            return new ResultsWfesSweep();
    }

}

ResultsWfesSweep *wfes_sweep::fixation(dvec s, dvec u, dvec v) {
    try {
        //Notify building matrix.
        this->notify(ExecutionStatus::BUILDING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }

        dmat switching(2, 2); switching << 1 - ConfigWfesSweep::l, ConfigWfesSweep::l, 0, 1;

        wrightfisher::Matrix wf = wrightfisher::NonAbsorbingToFixationOnly(ConfigWfesSweep::population_size, s, ConfigWfesSweep::h, u, v, switching, ConfigWfesSweep::a, msg_level, ConfigWfesSweep::b, ConfigWfesSweep::library);

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }

        //Save data into file.
        if (ConfigWfesSweep::output_Q)
            utils::writeSparseMatrixToFile(wf.Q, ConfigWfesSweep::path_output_Q, "WFES-Sweep-Fixation");
        if (ConfigWfesSweep::output_R)
            utils::writeMatrixToFile(wf.R, ConfigWfesSweep::path_output_R, "WFES-Sweep-Fixation");

        //Notify solving
        this->notify(ExecutionStatus::SOLVING_MATRICES);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }

        wf.Q->subtractIdentity();

        Solver* solver = SolverFactory::createSolver(ConfigWfesSweep::library, *(wf.Q), MKL_PARDISO_MATRIX_TYPE_REAL_UNSYMMETRIC, msg_level, ConfigWfesSweep::vienna_solver);

        solver->preprocess();

        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }
        dvec id(wf.Q->num_rows);
        id.setZero();
        id(ConfigWfesSweep::starting_copies) = 1;

        dvec N(wf.Q->num_rows);
        N = solver->solve(id, true);

        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }
        double T_fix = N.tail(2 * ConfigWfesSweep::population_size).sum();
        qDebug() << "Fixation";
        double rate = 1.0 / T_fix;

        llong size = ((2 * ConfigWfesSweep::population_size) + 1) + (2 * ConfigWfesSweep::population_size);

        dvec R_ext = wf.R.col(0);
        dvec B_ext = solver->solve(R_ext, false);

        dvec B_fix = dvec::Ones(size) - B_ext;

        //Notify saving data.
        this->notify(ExecutionStatus::SAVING_DATA);
        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }

        //Save data into file.
        dmat B(size, 2);
        if (ConfigWfesSweep::output_N)
            utils::writeMatrixToFile(N, ConfigWfesSweep::path_output_N, "WFES-Sweep-Fixation");
        if (ConfigWfesSweep::output_B) {
            B.col(0) = B_ext;
            B.col(1) = B_fix;
            utils::writeMatrixToFile(B, ConfigWfesSweep::path_output_B, "WFES-Sweep-Fixation");
        }
        delete solver;

        if(QThread::currentThread()->isInterruptionRequested()) {
            this->notify(ExecutionStatus::ABORTED);
            return new ResultsWfesSweep();
        }

        if(GlobalConfiguration::generateImages) {
            // Generate images.
            QImage *imageI = nullptr, *imageQ = nullptr, *imageR = nullptr,  *imageN = nullptr, *imageB = nullptr;
            if(ConfigWfesSweep::output_I) {
                imageI = utils::generateImage(starting_copies_p);
                ImageResults::I = imageI;
            }
            if(ConfigWfesSweep::output_Q) {
                imageQ = utils::generateImage(wf.Q->dense());
                ImageResults::Q = imageQ;
            }
            if(ConfigWfesSweep::output_R) {
                imageR = utils::generateImage(wf.R);
                ImageResults::R = imageR;
            }
            if(ConfigWfesSweep::output_N) {
                imageN = utils::generateImage(N);
                ImageResults::N = imageN;
            }
            if(ConfigWfesSweep::output_B) {
                imageB = utils::generateImage(B);
                ImageResults::B = imageB;
            }
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
    } catch(const std::exception &e) {
        this->notify(executionStatusToInt(ExecutionStatus::EXECUTION_ERROR));
        return new ResultsWfesSweep(e.what());
    }
}

void wfes_sweep::calculateStartingCopies(dvec s, dvec u, dvec v) {
    dvec first_row = wrightfisher::binom_row(2 * ConfigWfesSweep::population_size, wrightfisher::psi_diploid(0, ConfigWfesSweep::population_size, s(0), ConfigWfesSweep::h(0), u(0), v(0)), ConfigWfesSweep::a).Q;
    starting_copies_p = first_row.tail(first_row.size() - 1); // renormalize
    starting_copies_p /= 1 - first_row(0);
}

void wfes_sweep::calculateZ() {
    z = 0;

    if(ConfigWfesSweep::integration_cutoff <= 0) { // no integration
        z = 1;
        starting_copies_p[0] = 1;
    } else {
        for(llong i = 0; starting_copies_p(i) > ConfigWfesSweep::integration_cutoff; i++, z++);
    }
    if(ConfigWfesSweep::starting_copies != 0) z = 1;
}
