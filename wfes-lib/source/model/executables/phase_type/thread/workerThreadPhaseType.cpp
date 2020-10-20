#include "workerThreadPhaseType.h"


WorkerThreadPhaseType::WorkerThreadPhaseType(QObject *parent) : QThread(parent) {
    results = ResultsPhaseType();
}

WorkerThreadPhaseType::~WorkerThreadPhaseType()
{
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadPhaseType::run()
{
    QString result;
    phase_type single = phase_type();
    single.addObserver(this);
    results = *single.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadPhaseType::update(int value)
{
    emit updateProgress(value);
}
