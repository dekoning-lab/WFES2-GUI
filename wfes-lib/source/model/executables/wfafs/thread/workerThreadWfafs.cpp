#include "workerThreadWfafs.h"

WorkerThreadWfafs::WorkerThreadWfafs(QObject *parent) : QThread(parent) {
    results = ResultsWfafs();
}

WorkerThreadWfafs::~WorkerThreadWfafs() {
    // If not done when finished, aborted by user.
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfafs::run() {
    QString result;
    wfafs w = wfafs();
    w.addObserver(this);
    results = *w.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfafs::update(int value) {
    emit updateProgress(value);
}
