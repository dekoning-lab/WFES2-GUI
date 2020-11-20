#include "workerThreadPhaseType.h"

WorkerThreadPhaseType::WorkerThreadPhaseType(QObject *parent) : QThread(parent) {
    results = ResultsPhaseType();
}

WorkerThreadPhaseType::~WorkerThreadPhaseType() {
    // If not done when finished, aborted by user.
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadPhaseType::run() {
    QString result;
    phase_type exec = phase_type();
    exec.addObserver(this);
    results = *exec.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadPhaseType::update(int value) {
    emit updateProgress(value);
}
