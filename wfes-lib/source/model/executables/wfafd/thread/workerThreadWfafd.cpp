#include "workerThreadWfafd.h"

WorkerThreadWfafd::WorkerThreadWfafd(QObject *parent) : QThread(parent) {
    results = ResultsWfafd();
}

WorkerThreadWfafd::~WorkerThreadWfafd() {
    // If not done when finished, aborted by user.
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfafd::run() {
    QString result;
    wfafd w = wfafd();
    w.addObserver(this);
    results = *w.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfafd::update(int value) {
    emit updateProgress(value);
}
