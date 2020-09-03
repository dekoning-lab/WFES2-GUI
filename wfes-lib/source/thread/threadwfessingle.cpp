#include "threadwfessingle.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent) {}

WorkerThread::~WorkerThread() {
    if (!done)
        emit updateProgress(ExecutionStatus::ABORTED);
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
