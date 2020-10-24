#ifndef WORKERTHREADWFESSEQUENTIAL_H
#define WORKERTHREADWFESSEQUENTIAL_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>


#include <QString>
#include <QThread>

#include <cmath>
#include <boost/format.hpp>
#include <utils/observer/observer.h>
#include "utils/utils.h"
#include <source/model/executables/wfes_sequential/results/resultsWfesSequential.h>
#include <model/executables/wfes_sequential/wfes_sequential.h>

#include "source/model/executables/wfes_sequential/config/configWfesSequential.h"


class WorkerThreadWfesSequential : public QThread, public Observer
{
    Q_OBJECT

    public:
        /**
         * @brief Store results of an execution.
         */
        ResultsWfesSequential results;

        bool done = false;

        explicit WorkerThreadWfesSequential(QObject* parent = nullptr);

        ~WorkerThreadWfesSequential();

        void run() override;

        void update(int value) override;

    signals:
        void resultReady(ResultsWfesSequential results);
        void updateProgress(int progress);
};

#endif // WORKERTHREADWFESSEQUENTIAL_H
