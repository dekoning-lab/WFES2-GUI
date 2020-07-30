#ifndef WFESLIB_H
#define WFESLIB_H

#include "wfes-lib_global.h"
#include "model/wfes_single.h"

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QDebug>

class WFESLIBSHARED_EXPORT WfesLib : public QObject
{
    Q_OBJECT

    public:
        explicit WfesLib(QObject* parent = nullptr);
        ~WfesLib();
        void execute();
};

#endif // WFESLIB_H
