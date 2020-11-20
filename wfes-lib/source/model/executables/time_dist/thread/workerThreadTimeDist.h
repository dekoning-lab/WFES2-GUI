#ifndef WORKERTHREADTIMEDIST_H
#define WORKERTHREADTIMEDIST_H

#include <QThread>

#include "model/executables/time_dist/results/resultsTimeDist.h"
#include "model/executables/time_dist/time_dist.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadTimeDist class implements a Worker Thread that executes everything in a background thread.
 * Observes time dist for updating progress in GUI.
 */
class WorkerThreadTimeDist : public QThread, public Observer {
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsTimeDist results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadTimeDist Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadTimeDist(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadPhaseType Destructor.
         */
        ~WorkerThreadTimeDist();

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
        void resultReady(ResultsTimeDist results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);
};

#endif // WORKERTHREADTIMEDIST_H
