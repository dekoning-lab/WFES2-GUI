#include "workerThreadWfesSequential.h"

WorkerThreadWfesSequential::WorkerThreadWfesSequential(QObject *parent) : QThread(parent) {
    results = ResultsWfesSequential();
}

WorkerThreadWfesSequential::~WorkerThreadWfesSequential(){
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfesSequential::run() {
    QString result;
    wfes_sequential sequential = wfes_sequential();
    wfes_sequential.addObserver(this);
    results = *wfes_sequential.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfesSequential::update(int value)
{
    emit updateProgress(value);
}
