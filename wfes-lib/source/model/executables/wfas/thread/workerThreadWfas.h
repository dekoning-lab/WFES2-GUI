#ifndef WORKERTHREADWFAS_H
#define WORKERTHREADWFAS_H

#include <QThread>

#include "model/executables/wfas/results/resultsWfas.h"
#include "model/executables/wfas/wfas.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadWfas class implements a Worker Thread that executes everything in a background thread.
 * Observes wfas for updating progress in GUI.
 */
class WorkerThreadWfas : public QThread, public Observer {
    Q_OBJECT
    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfas results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfas Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfas(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadPhaseType Destructor.
         */
        ~WorkerThreadWfas();

        /**
         * @brief Start execution. Overrided from QThread.
         */
        void run() override;

        /**
         * @brief Handle progress of an execution and notify GUI of the progress.
         * @param value Progress message position in the array wfes::utils::ExecutionStatusName.
         */
        void update(int value) override;

    signals:
        /**
         * @brief Signal for notifying when results are ready
         */
        void resultReady(ResultsWfas results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFAS_H
