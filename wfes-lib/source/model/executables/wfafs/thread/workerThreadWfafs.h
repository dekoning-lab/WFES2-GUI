#ifndef WORKERTHREADWFAFS_H
#define WORKERTHREADWFAFS_H

#include <QThread>

#include "model/executables/wfafs/results/resultsWfafs.h"
#include "model/executables/wfafs/wfafs.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadWfafs class implements a Worker Thread that executes everything in a background thread.
 * Observes wfafs for updating progress in GUI.
 */
class WorkerThreadWfafs : public QThread, public Observer {
    Q_OBJECT
    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfafs results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfafs Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfafs(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadPhaseType Destructor.
         */
        ~WorkerThreadWfafs();

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
        void resultReady(ResultsWfafs results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFAFS_H
