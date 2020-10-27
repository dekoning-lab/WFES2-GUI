#ifndef WORKERTHREADWFESSWITCHING_H
#define WORKERTHREADWFESSWITCHING_H

#include <QThread>

#include <utils/observer/observer.h>
#include <utils/utils.h>

#include <model/executables/wfes_switching/results/resultsWfesSwitching.h>

#include <model/executables/wfes_switching/wfes_switching.h>



class WorkerThreadWfesSwitching : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSwitching results;

        bool done = false;

        explicit WorkerThreadWfesSwitching(QObject* parent = nullptr);

        ~WorkerThreadWfesSwitching();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsWfesSwitching results);
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFESSWITCHING_H
