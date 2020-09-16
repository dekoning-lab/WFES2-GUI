#ifndef THREADWFESSINGLE_H
#define THREADWFESSINGLE_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>


#include <QString>
#include <QThread>

#include <cmath>
#include <boost/format.hpp>
#include <utils/observer/observer.h>
#include <results/results.h>
#include <model/wfes_single.h>

#include "config/config.h"


class WorkerThread : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        Results results;

        bool done = false;

        explicit WorkerThread(QObject* parent = nullptr);

        ~WorkerThread();

        void run() override;


        void update(int value) override;

    signals:
        void resultReady(Results results);
        void updateProgress(int progress);
};

#endif // THREADWFESSINGLE_H
