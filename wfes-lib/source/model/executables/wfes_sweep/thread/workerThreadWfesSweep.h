#ifndef WORKERTHREADWFESSWEEP_H
#define WORKERTHREADWFESSWEEP_H

#include <QThread>

#include <utils/observer/observer.h>
#include <utils/utils.h>

#include <model/executables/wfes_sweep/results/resultsWfesSweep.h>

#include <model/executables/wfes_sweep/wfes_sweep.h>



class WorkerThreadWfesSweep : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSweep results;

        bool done = false;

        explicit WorkerThreadWfesSweep(QObject* parent = nullptr);

        ~WorkerThreadWfesSweep();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsWfesSweep results);
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFESSWEEP_H
