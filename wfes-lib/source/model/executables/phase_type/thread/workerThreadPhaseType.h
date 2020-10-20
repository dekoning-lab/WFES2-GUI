#ifndef WORKERTHREADPHASETYPE_H
#define WORKERTHREADPHASETYPE_H

#include <QThread>

#include <utils/observer/observer.h>
#include <utils/utils.h>

#include <model/executables/phase_type/results/resultsPhaseType.h>

#include <model/executables/phase_type/phase_type.h>

class WorkerThreadPhaseType : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsPhaseType results;

        bool done = false;

        explicit WorkerThreadPhaseType(QObject* parent = nullptr);

        ~WorkerThreadPhaseType();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsPhaseType results);
        void updateProgress(int progress);
};

#endif // WORKERTHREADPHASETYPE_H
