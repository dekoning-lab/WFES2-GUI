#ifndef WORKERTHREADPHASETYPE_H
#define WORKERTHREADPHASETYPE_H

#include <QThread>

#include <model/executables/phase_type/results/resultsPhaseType.h>
#include <model/executables/phase_type/phase_type.h>
#include <utils/observer/observer.h>
#include <utils/utils.h>

/**
 * @brief The WorkerThreadPhaseType class implements a Worker Thread that executes everything in a background thread.
 * Observes phase type for updating progress in GUI.
 */
class WorkerThreadPhaseType : public QThread, public Observer {
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsPhaseType results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadPhaseType Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadPhaseType(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadPhaseType Destructor.
         */
        ~WorkerThreadPhaseType();

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
        void resultReady(ResultsPhaseType results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);
};

#endif // WORKERTHREADPHASETYPE_H
