#include "threadwfessingle.h"


WorkerThread::WorkerThread(QObject *parent) : QThread(parent) {
    results = ResultsWfesSingle();
}

WorkerThread::~WorkerThread() {
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThread::run() {
    QString result;
    wfes_single single = wfes_single();
    single.addObserver(this);
    results = *single.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThread::update(int value) {
    emit updateProgress(value);
}




