#include "workerThreadWfesSingle.h"


WorkerThreadWfesSingle::WorkerThreadWfesSingle(QObject *parent) : QThread(parent) {
    results = ResultsWfesSingle();
}

WorkerThreadWfesSingle::~WorkerThreadWfesSingle() {
    // If not done when finished, aborted by user.
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfesSingle::run() {
    QString result;
    wfes_single single = wfes_single();
    single.addObserver(this);
    results = *single.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfesSingle::update(int value) {
    emit updateProgress(value);
}
