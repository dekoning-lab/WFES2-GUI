#include "workerThreadWfesSwitching.h"

WorkerThreadWfesSwitching::WorkerThreadWfesSwitching(QObject *parent) : QThread(parent) {
    results = ResultsWfesSwitching();
}

WorkerThreadWfesSwitching::~WorkerThreadWfesSwitching()
{
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfesSwitching::run()
{
    QString result;
    wfes_switching switching = wfes_switching();
    switching.addObserver(this);
    results = *switching.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfesSwitching::update(int value)
{
    emit updateProgress(value);
}
