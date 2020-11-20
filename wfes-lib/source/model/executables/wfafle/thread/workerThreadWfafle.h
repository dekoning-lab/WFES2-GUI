#ifndef WORKERTHREADWFAFLE_H
#define WORKERTHREADWFAFLE_H

#include <QThread>

#include "model/executables/wfafle/results/resultsWfafle.h"
#include "model/executables/wfafle/wfafle.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadWfafle class implements a Worker Thread that executes everything in a background thread.
 * Observes wfafle for updating progress in GUI.
 */
class WorkerThreadWfafle : public QThread, public Observer {
    Q_OBJECT
    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfafle results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfafle Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfafle(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadPhaseType Destructor.
         */
        ~WorkerThreadWfafle();

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
        void resultReady(ResultsWfafle results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFAFLE_H
