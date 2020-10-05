#include "workerThreadTimeDist.h"

WorkerThreadTimeDist::WorkerThreadTimeDist(QObject *parent) : QThread(parent)
{
    results = ResultsTimeDist();
}

WorkerThreadTimeDist::~WorkerThreadTimeDist()
{
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadTimeDist::run()
{
    time_dist single = time_dist();
    single.addObserver(this);
    results = *single.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadTimeDist::update(int value)
{
    emit updateProgress(value);
}
