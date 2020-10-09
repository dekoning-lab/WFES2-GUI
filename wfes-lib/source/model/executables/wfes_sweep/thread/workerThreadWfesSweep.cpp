#include "workerThreadWfesSweep.h"

#include <model/executables/wfes_sweep/wfes_sweep.h>

WorkerThreadWfesSweep::WorkerThreadWfesSweep(QObject *parent) : QThread(parent) {
    results = ResultsWfesSweep();
}

WorkerThreadWfesSweep::~WorkerThreadWfesSweep()
{
    if (!done) {
        exit();
        emit updateProgress(wfes::utils::ExecutionStatus::ABORTED);
    } else {
        exit();
    }
}

void WorkerThreadWfesSweep::run()
{
    QString result;
    wfes_sweep single = wfes_sweep();
    single.addObserver(this);
    results = *single.execute();

    done = true;
    emit resultReady(results);
}

void WorkerThreadWfesSweep::update(int value)
{
    emit updateProgress(value);
}
