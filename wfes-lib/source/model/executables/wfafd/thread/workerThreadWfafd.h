#ifndef WORKERTHREADWFAFD_H
#define WORKERTHREADWFAFD_H

#include <QThread>

#include "model/executables/wfafd/results/resultsWfafd.h"
#include "model/executables/wfafd/wfafd.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadWfafd class implements a Worker Thread that executes everything in a background thread.
 * Observes wfafd for updating progress in GUI.
 */
class WorkerThreadWfafd : public QThread, public Observer {
    Q_OBJECT
    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfafd results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfafd Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfafd(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadPhaseType Destructor.
         */
        ~WorkerThreadWfafd();

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
        void resultReady(ResultsWfafd results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);

};

#endif // RESULTSWFAFD_H
