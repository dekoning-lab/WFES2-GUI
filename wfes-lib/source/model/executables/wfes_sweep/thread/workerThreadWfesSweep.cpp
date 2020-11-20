#include "workerThreadWfesSweep.h"

WorkerThreadWfesSweep::WorkerThreadWfesSweep(QObject *parent) : QThread(parent) {
    results = ResultsWfesSweep();
}

WorkerThreadWfesSweep::~WorkerThreadWfesSweep() {
    // If not done when finished, aborted by user.
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfesSweep::run() {
    QString result;
    wfes_sweep sweep = wfes_sweep();
    sweep.addObserver(this);
    results = *sweep.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfesSweep::update(int value) {
    emit updateProgress(value);
}
