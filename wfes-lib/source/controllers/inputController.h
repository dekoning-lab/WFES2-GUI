#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/wfes_single.h"

#include "results/results.h"

#include <QString>
#include "math.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT InputController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_n READ get_n WRITE set_n NOTIFY input_changed)

            public:
                explicit InputController(QObject* parent = nullptr);
                ~InputController();

                QString get_n() const;
                void set_n(QString n) const;

            signals:
                void input_changed();
        };

    }
}

#endif //INPUTCONTROLLER_H
