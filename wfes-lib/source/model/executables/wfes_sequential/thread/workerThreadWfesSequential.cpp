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
}

void WorkerThreadWfesSequential::update(int value)
{
    emit updateProgress(value);
}
