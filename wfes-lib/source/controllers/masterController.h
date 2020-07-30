#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/wfes_single.h"

#include <QString>

namespace wfes {
    namespace controllers {
        class WFESLIBSHARED_EXPORT MasterController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_welcomeMessage MEMBER welcomeMessage CONSTANT)
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)

            public:
                QString welcomeMessage = "This is MasterController.";
                explicit MasterController(QObject* parent = nullptr);
                QString execute();
        };
    }
}

#endif //MASTERCONTROLLER_H
