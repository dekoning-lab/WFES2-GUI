#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/wfes_single.h"

#include "results/results.h"

#include <QString>
#include "math.h"
#include <boost/format.hpp>

namespace wfes {
    namespace controllers {
        class WFESLIBSHARED_EXPORT OutputController : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_get_p_ext READ get_p_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_p_fix READ get_p_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_abs READ get_t_abs NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_abs_std READ get_t_abs_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_ext READ get_t_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_ext_std READ get_t_ext_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_n_ext READ get_n_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix READ get_t_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix_std READ get_t_fix_std NOTIFY results_changed)

            public:
                // Store results of an execution.
                Results* results = new Results();

                explicit OutputController(QObject* parent = nullptr);
                ~OutputController();

                QString execute();

                QString get_p_ext() const;
                QString get_p_fix() const;
                QString get_t_abs() const;
                QString get_t_abs_std() const;
                QString get_t_ext() const;
                QString get_t_ext_std() const;
                QString get_n_ext() const;
                QString get_t_fix() const;
                QString get_t_fix_std() const;

            signals:
                void results_changed();
        };
    }
}

#endif //MASTERCONTROLLER_H
