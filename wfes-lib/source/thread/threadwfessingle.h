#ifndef THREADWFESSINGLE_H
#define THREADWFESSINGLE_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>


#include <QString>
#include <QThread>

#include <cmath>
#include <boost/format.hpp>

#include "config/config.h"


class WFESLIBSHARED_EXPORT WorkerThread : public QThread
{
    Q_OBJECT

    public:
        bool done = false;

        explicit WorkerThread(QObject* parent = nullptr);

        ~WorkerThread();

        void run() override;


    signals:
        void updateProgress(int progress);
};


#endif // THREADWFESSINGLE_H
