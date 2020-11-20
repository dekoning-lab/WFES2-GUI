#include "workerThreadTimeDist.h"

WorkerThreadTimeDist::WorkerThreadTimeDist(QObject *parent) : QThread(parent) {
    results = ResultsTimeDist();
}

WorkerThreadTimeDist::~WorkerThreadTimeDist() {
    // If not done when finished, aborted by user.
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadTimeDist::run() {
    time_dist exec = time_dist();
    exec.addObserver(this);
    results = *exec.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadTimeDist::update(int value) {
    emit updateProgress(value);
}
