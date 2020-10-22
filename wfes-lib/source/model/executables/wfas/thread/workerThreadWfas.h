#ifndef WORKERTHREADWFAS_H
#define WORKERTHREADWFAS_H

#include <QThread>

#include <model/executables/wfas/results/resultsWfas.h>

#include <model/executables/wfas/wfas.h>


#include <utils/observer/observer.h>
#include <utils/utils.h>

class WorkerThreadWfas : public QThread, public Observer
{
    Q_OBJECT
    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfas results;

        bool done = false;

        explicit WorkerThreadWfas(QObject* parent = nullptr);

        ~WorkerThreadWfas();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsWfas results);
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFAS_H
