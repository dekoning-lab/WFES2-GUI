#ifndef WORKERTHREADWFESSEQUENTIAL_H
#define WORKERTHREADWFESSEQUENTIAL_H

#include <QThread>

#include "model/executables/wfes_sequential/results/resultsWfesSequential.h"
#include "model/executables/wfes_sequential/wfes_sequential.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadWfesSequential class implements a Worker Thread that executes everything in a background thread.
 * Observes wfes sequential for updating progress in GUI.
 */
class WorkerThreadWfesSequential : public QThread, public Observer {
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSequential results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfesSequential Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfesSequential(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadWfesSequential Destructor.
         */
        ~WorkerThreadWfesSequential();

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
        void resultReady(ResultsWfesSequential results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);
};

#endif // WORKERTHREADWFESSEQUENTIAL_H
