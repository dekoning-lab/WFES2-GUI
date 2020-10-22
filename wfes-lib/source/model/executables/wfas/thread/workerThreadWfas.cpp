#include "workerThreadWfas.h"

WorkerThreadWfas::WorkerThreadWfas(QObject *parent) : QThread(parent) {
    results = ResultsWfas();
}

WorkerThreadWfas::~WorkerThreadWfas()
{
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfas::run()
{
    QString result;
    wfas w = wfas();
    w.addObserver(this);
    results = *w.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfas::update(int value)
{
    emit updateProgress(value);
}
