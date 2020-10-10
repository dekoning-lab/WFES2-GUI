#ifndef OUTPUTCONTROLLER_H
#define OUTPUTCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>
#include "model/executables/wfes_single/wfes_single.h"

#include "source/model/executables/wfes_single/results/resultsWfesSingle.h"

#include "utils/utils.h"

#include <QString>
#include <QThread>

#include "math.h"
#include <boost/format.hpp>

#include "source/model/executables/wfes_single/config/configWfesSingle.h"

#include "source/model/executables/wfes_single/thread/workerThreadWfesSingle.h"

namespace wfes {
    namespace controllers {

        /**
         * @brief The OutputController class contains output values of the application, e.g., the results of an execution.
         */
        class WFESLIBSHARED_EXPORT OutputControllerWfesSingle : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
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
            Q_PROPERTY(QString ui_get_time READ get_time NOTIFY results_changed)
            Q_PROPERTY(bool ui_get_not_exec READ get_not_exec NOTIFY results_changed)
            Q_PROPERTY(QString ui_progress READ get_progress NOTIFY updateProgress)

            public:

                ResultsWfesSingle results;

                bool executing;

                WorkerThreadWfesSingle* worker;

                QString progress = "";

                /**
                 * @brief OutputControllerWfesSingle constructor
                 * @param parent To be used by Qt.
                 */
                explicit OutputControllerWfesSingle(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerWfesSingle Destructor.
                 */
                ~OutputControllerWfesSingle();

                /**
                 * @brief Execute wfes_single and get results.
                 * @return Results of wfes_single execution.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of wfes_single.
                 * @return Nothing.
                 */
                QString stop();

                /**
                 * @brief Send p_ext to GUI.
                 * @return QString containing p_ext.
                 */
                QString get_p_ext() const;

                /**
                 * @brief Send p_fix to GUI.
                 * @return QString containing p_fix.
                 */
                QString get_p_fix() const;

                /**
                 * @brief Send t_abs to GUI.
                 * @return QString containing t_abs.
                 */
                QString get_t_abs() const;

                /**
                 * @brief Send t_abs_std to GUI.
                 * @return QString containing t_abs_std.
                 */
                QString get_t_abs_std() const;

                /**
                 * @brief Send t_ext to GUI.
                 * @return QString containing t_ext.
                 */
                QString get_t_ext() const;

                /**
                 * @brief Send t_ext_std to GUI.
                 * @return QString containing t_ext_std.
                 */
                QString get_t_ext_std() const;

                /**
                 * @brief Send n_ext to GUI.
                 * @return QString containing n_ext.
                 */
                QString get_n_ext() const;

                /**
                 * @brief Send t_fix to GUI.
                 * @return QString containing t_fix.
                 */
                QString get_t_fix() const;

                /**
                 * @brief Send t_fix_std to GUI.
                 * @return QString containing t_fix_std.
                 */
                QString get_t_fix_std() const;

                /**
                 * @brief Send rate to GUI.
                 * @return QString containing rate.
                 */
                QString get_rate() const;

                /**
                 * @brief Send e_freq_mut to GUI.
                 * @return QString containing e_freq_mut.
                 */
                QString get_e_freq_mut() const;

                /**
                 * @brief Send e_freq_wt to GUI.
                 * @return QString containing e_freq_wt.
                 */
                QString get_e_freq_wt() const;

                /**
                 * @brief Send f_est to GUI.
                 * @return QString containing f_est.
                 */
                QString get_f_est() const;

                /**
                 * @brief Send p_est to GUI.
                 * @return QString containing p_est.
                 */
                QString get_p_est() const;

                /**
                 * @brief Send t_seg to GUI.
                 * @return QString containing t_seg.
                 */
                QString get_t_seg() const;

                /**
                 * @brief Send t_seg_std to GUI.
                 * @return QString containing t_seg_std.
                 */
                QString get_t_seg_std() const;

                /**
                 * @brief Send t_seg_est to GUI.
                 * @return QString containing t_seg_est.
                 */
                QString get_t_seg_est() const;

                /**
                 * @brief Send t_seg_est_std to GUI.
                 * @return QString containing t_seg_est_std.
                 */
                QString get_t_seg_est_std() const;

                /**
                 * @brief Send t_seg_fix to GUI.
                 * @return QString containing t_seg_fix.
                 */
                QString get_t_seg_fix() const;

                /**
                 * @brief Send t_seg_fix_std to GUI.
                 * @return QString containing t_seg_fix_std.
                 */
                QString get_t_seg_fix_std() const;

                /**
                 * @brief Send t_est to GUI.
                 * @return QString containing t_est.
                 */
                QString get_t_est() const;

                /**
                 * @brief Send t_est_std to GUI.
                 * @return QString containing t_est_std.
                 */
                QString get_t_est_std() const;

                /**
                 * @brief Send e_a to GUI.
                 * @return QString containing e_a.
                 */
                QString get_e_a() const;

                /**
                 * @brief Send s_a to GUI.
                 * @return QString containing s_a.
                 */
                QString get_s_a() const;

                /**
                 * @brief Send error_message to GUI.
                 * @return QString containing error_message.
                 */
                QString get_error_message() const;

                /**
                 * @brief Reset error message.
                 * @return QString empty.
                 */
                QString reset_error() const;

                /**
                 * @brief Send execution time to GUI.
                 * @return QString containing execution time.
                 */
                QString get_time() const;

                /**
                 * @brief Send if the background thread is executing.
                 * @return Boolean telling if the background thread is executing.
                 */
                bool get_not_exec() const;

                QString get_progress() const;

            public slots:
                void handleResults(ResultsWfesSingle results){
                    this->results = results;
                    this->executing = false;
                    emit results_changed();
                }
                void handleProgress(int progress){
                    this->progress = wfes::utils::ExecutionStatusName[progress];
                    emit updateProgress();
                }

            signals:
                /**
                 * @brief Signal for notifying when results has been calculated/changed in backend.
                 */
                void results_changed();
                void operate();
                void updateProgress();
        };
    }
}

#endif //OUTPUTCONTROLLER_H
