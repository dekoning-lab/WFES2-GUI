#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/wfes_single.h"

#include "results/results.h"

#include <QString>
#include "math.h"

namespace wfes {
    namespace controllers {
        class WFESLIBSHARED_EXPORT MasterController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_results READ getResults NOTIFY resultsChanged)

            public:
                Results* results = new Results();
                QString getResults() const;
                explicit MasterController(QObject* parent = nullptr);
                QString execute();

            signals:
                void resultsChanged();
        };
    }
}

#endif //MASTERCONTROLLER_H
