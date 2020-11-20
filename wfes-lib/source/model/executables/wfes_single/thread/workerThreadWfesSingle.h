#ifndef THREADWFESSINGLE_H
#define THREADWFESSINGLE_H

#include <QThread>

#include "model/executables/wfes_single/results/resultsWfesSingle.h"
#include "model/executables/wfes_single/wfes_single.h"
#include "utils/observer/observer.h"
#include "utils/utils.h"

/**
 * @brief The WorkerThreadWfesSingle class implements a Worker Thread that executes everything in a background thread.
 * Observes wfes single for updating progress in GUI.
 */
class WorkerThreadWfesSingle : public QThread, public Observer {
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSingle results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfesSingle Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfesSingle(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadWfesSingle Destructor.
         */
        ~WorkerThreadWfesSingle();

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
        void resultReady(ResultsWfesSingle results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);
};

#endif // THREADWFESSINGLE_H
