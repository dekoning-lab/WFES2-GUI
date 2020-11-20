#ifndef WORKERTHREADWFESSWEEP_H
#define WORKERTHREADWFESSWEEP_H

#include <QThread>

#include <model/executables/wfes_sweep/results/resultsWfesSweep.h>
#include <model/executables/wfes_sweep/wfes_sweep.h>
#include <utils/observer/observer.h>
#include <utils/utils.h>

class WorkerThreadWfesSweep : public QThread, public Observer {
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSweep results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfesSingle Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfesSweep(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadWfesSingle Destructor.
         */
        ~WorkerThreadWfesSweep();

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
        void resultReady(ResultsWfesSweep results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFESSWEEP_H
