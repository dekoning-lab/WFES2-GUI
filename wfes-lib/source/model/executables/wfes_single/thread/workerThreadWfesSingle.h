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
#include "utils/utils.h"
#include <source/model/executables/wfes_single/results/resultsWfesSingle.h>
#include <model/executables/wfes_single/wfes_single.h>

#include "source/model/executables/wfes_single/config/configWfesSingle.h"


class WorkerThreadWfesSingle : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSingle results;

        bool done = false;

        explicit WorkerThreadWfesSingle(QObject* parent = nullptr);

        ~WorkerThreadWfesSingle();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsWfesSingle results);
        void updateProgress(int progress);
};

#endif // THREADWFESSINGLE_H
