#ifndef OUTPUTCONTROLLER_H
#define OUTPUTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/wfes_single.h"

#include "results/results.h"

#include <QString>
#include "math.h"
#include <boost/format.hpp>

#include "config/config.h"

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
            Q_PROPERTY(QString ui_get_rate READ get_rate NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_e_freq_mut READ get_e_freq_mut NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_e_freq_wt READ get_e_freq_wt NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_f_est READ get_f_est NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_p_est READ get_p_est NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_seg READ get_t_seg NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_seg_std READ get_t_seg_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_seg_est READ get_t_seg_est NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_seg_est_std READ get_t_seg_est_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_seg_fix READ get_t_seg_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_seg_fix_std READ get_t_seg_fix_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_est READ get_t_est NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_est_std READ get_t_est_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_e_a READ get_e_a NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_s_a READ get_s_a NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_error_message READ get_error_message NOTIFY results_changed)
            Q_PROPERTY(QString ui_reset_error READ reset_error NOTIFY results_changed)

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
                QString get_rate() const;
                QString get_e_freq_mut() const;
                QString get_e_freq_wt() const;
                QString get_f_est() const;
                QString get_p_est() const;
                QString get_t_seg() const;
                QString get_t_seg_std() const;
                QString get_t_seg_est() const;
                QString get_t_seg_est_std() const;
                QString get_t_seg_fix() const;
                QString get_t_seg_fix_std() const;
                QString get_t_est() const;
                QString get_t_est_std() const;
                QString get_e_a() const;
                QString get_s_a() const;
                QString get_error_message() const;
                QString reset_error() const;

            signals:
                void results_changed();
        };
    }
}

#endif //OUTPUTCONTROLLER_H
