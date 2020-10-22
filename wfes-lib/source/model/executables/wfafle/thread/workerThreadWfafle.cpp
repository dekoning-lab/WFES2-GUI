#include "workerThreadWfafle.h"

WorkerThreadWfafle::WorkerThreadWfafle(QObject *parent) : QThread(parent) {
    results = ResultsWfafle();
}

WorkerThreadWfafle::~WorkerThreadWfafle()
{
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfafle::run()
{
    QString result;
    wfafle w = wfafle();
    w.addObserver(this);
    results = *w.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfafle::update(int value)
{
    emit updateProgress(value);
}
