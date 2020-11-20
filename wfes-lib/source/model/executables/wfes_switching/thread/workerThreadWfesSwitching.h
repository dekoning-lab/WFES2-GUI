#ifndef WORKERTHREADWFESSWITCHING_H
#define WORKERTHREADWFESSWITCHING_H

#include <QThread>

#include <model/executables/wfes_switching/results/resultsWfesSwitching.h>
#include <model/executables/wfes_switching/wfes_switching.h>
#include <utils/observer/observer.h>
#include <utils/utils.h>

class WorkerThreadWfesSwitching : public QThread, public Observer {
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSwitching results;

        /**
         * @brief Indicates if the execution has finished.
         */
        bool done = false;

        /**
         * @brief WorkerThreadWfesSingle Constructor
         * @param parent To be used by Qt.
         */
        explicit WorkerThreadWfesSwitching(QObject* parent = nullptr);

        /**
         * @brief WorkerThreadWfesSingle Destructor.
         */
        ~WorkerThreadWfesSwitching();

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
        void resultReady(ResultsWfesSwitching results);

        /**
         * @brief Signal for notifying progress of an execution.
         */
        void updateProgress(int progress);

};

#endif // WORKERTHREADWFESSWITCHING_H
