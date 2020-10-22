#ifndef WORKERTHREADWFAFLE_H
#define WORKERTHREADWFAFLE_H

#include <QThread>

#include <model/executables/wfafle/results/resultsWfafle.h>

#include <model/executables/wfafle/wfafle.h>

#include <utils/observer/observer.h>
#include <utils/utils.h>


class WorkerThreadWfafle : public QThread, public Observer
{
    Q_OBJECT
    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfafle results;

        bool done = false;

        explicit WorkerThreadWfafle(QObject* parent = nullptr);

        ~WorkerThreadWfafle();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsWfafle results);
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFAFLE_H
