#ifndef WORKERTHREADTIMEDIST_H
#define WORKERTHREADTIMEDIST_H

#include <QThread>

#include <utils/observer/observer.h>
#include "utils/utils.h"

#include <model/executables/time_dist/time_dist.h>

#include <model/executables/time_dist/results/resultsTimeDist.h>



class WorkerThreadTimeDist : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsTimeDist results;

        bool done = false;

        explicit WorkerThreadTimeDist(QObject* parent = nullptr);

        ~WorkerThreadTimeDist();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsTimeDist results);
        void updateProgress(int progress);
};

#endif // WORKERTHREADTIMEDIST_H
