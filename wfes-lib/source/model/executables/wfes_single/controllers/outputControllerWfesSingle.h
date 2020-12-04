#ifndef OUTPUTCONTROLLER_H
#define OUTPUTCONTROLLER_H

#include <QApplication>
#include <QClipboard>
#include <QObject>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include "source/model/executables/wfes_single/thread/workerThreadWfesSingle.h"

using namespace wfes::config;

namespace wfes {
    namespace controllers {

    /**
     * @brief The OutputControllerWfesSingle class is a controller for output parameters
     * and functions of wfes single.
     */
        class WFESLIBSHARED_EXPORT OutputControllerWfesSingle : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
            Q_PROPERTY(QString ui_save_config READ save_config CONSTANT)
            Q_PROPERTY(QString ui_load_config READ load_config CONSTANT)
            Q_PROPERTY(QString ui_get_p_ext READ get_p_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_p_fix READ get_p_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_abs READ get_t_abs NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_abs_std READ get_t_abs_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_ext READ get_t_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_ext_std READ get_t_ext_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_n_ext READ get_n_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix READ get_t_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix_std READ get_t_fix_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix_abs_mode READ get_t_fix_abs_mode NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix_std_abs_mode READ get_t_fix_std_abs_mode NOTIFY results_changed)
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

                /**
                 * @brief Results of an execution.
                 */
                ResultsWfesSingle results;

                /**
                 * @brief Indicate if phase type if being executed.
                 */
                bool executing;

                /**
                 * @brief WorkerThread that manages the background execution of wfes single.
                 */
                WorkerThreadWfesSingle* worker;

                /**
                 * @brief Message with the progress of an execution.
                 */
                QString progress = "";

                /**
                 * @brief OutputControllerWfesSingle constructor
                 * @param parent To be used by Qt.
                 */
                explicit OutputControllerWfesSingle(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerWfesSingle Destructor.
                 */
                ~OutputControllerWfesSingle() = default;

                /**
                 * @brief Execute wfes single and get results.
                 * @return Nothing.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of wfes single.
                 * @return Nothing.
                 */
                QString stop();

                /**
                 * @brief Save configuration of wfes single.
                 * @return Nothing.
                 */
                QString save_config();

                /**
                 * @brief Load configuration of wfes single.
                 * @return Nothing.
                 */
                QString load_config();

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
                 * @brief Send t_fix to GUI.
                 * @return QString containing t_fix.
                 */
                QString get_t_fix_abs_mode() const;

                /**
                 * @brief Send t_fix_std to GUI.
                 * @return QString containing t_fix_std.
                 */
                QString get_t_fix_std_abs_mode() const;

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
                QString reset_error();

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

                /**
                 * @brief Get progress message.
                 * @return Progress message.
                 */
                QString get_progress() const;

                Q_INVOKABLE void coppyToClipboard() {
                    QClipboard* clipboard = QApplication::clipboard();
                    QString text = "";
                    // Input parameters
                    text += QString::fromStdString("Parameter, Value") + "\n";
                    text += QString::fromStdString("N, " + (boost::format(DPF) % (ConfigWfesSingle::population_size)).str()) + "\n";
                    text += QString::fromStdString("a, " + (boost::format(DPF) % (ConfigWfesSingle::a)).str()) + "\n";
                    text += QString::fromStdString("c, " + (boost::format(DPF) % (ConfigWfesSingle::integration_cutoff)).str()) + "\n";
                    text += QString::fromStdString("s, " + (boost::format(DPF) % (ConfigWfesSingle::s)).str()) + "\n";
                    text += QString::fromStdString("h, " + (boost::format(DPF) % (ConfigWfesSingle::h)).str()) + "\n";
                    text += QString::fromStdString("u, " + (boost::format(DPF) % (ConfigWfesSingle::u)).str()) + "\n";
                    text += QString::fromStdString("v, " + (boost::format(DPF) % (ConfigWfesSingle::v)).str()) + "\n";

                    if(wfes::config::ConfigWfesSingle::modelType == wfes::config::ModelTypeWfesSingle::ABSORPTION) {
                        text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfesSingle::starting_copies)).str()) + "\n";
                        text += QString::fromStdString("m, ") + (ConfigWfesSingle::no_rem ? "true" : "false") + "\n";

                        // Output
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("P. ext., " + (boost::format(DPF) % (results.pExt)).str()) + "\n";
                        text += QString::fromStdString("P. fix., " + (boost::format(DPF) % (results.pFix)).str()) + "\n";
                        text += QString::fromStdString("T. abs., " + (boost::format(DPF) % (results.tAbs)).str()) + "\n";
                        text += QString::fromStdString("T. abs. std., " + (boost::format(DPF) % (results.tAbsStd)).str()) + "\n";
                        text += QString::fromStdString("T. ext., " + (boost::format(DPF) % (results.tExt)).str()) + "\n";
                        text += QString::fromStdString("T. ext. std., " + (boost::format(DPF) % (results.tExtStd)).str()) + "\n";
                        text += QString::fromStdString("N. ext., " + (boost::format(DPF) % (results.nExt)).str()) + "\n";
                        text += QString::fromStdString("T. fix., " + (boost::format(DPF) % (results.tFixAbsMode)).str()) + "\n";
                        text += QString::fromStdString("T. fix. std., " + (boost::format(DPF) % (results.tFixStdAbsMode)).str()) + "\n";
                    } else if (wfes::config::ConfigWfesSingle::modelType == wfes::config::ModelTypeWfesSingle::FIXATION) {
                        text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfesSingle::starting_copies)).str()) + "\n";
                        text += QString::fromStdString("m, ") + (ConfigWfesSingle::no_rem ? "true" : "false") + "\n";

                        // Output
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("T. fix., " + (boost::format(DPF) % (results.tFix)).str()) + "\n";
                        text += QString::fromStdString("T. fix. std., " + (boost::format(DPF) % (results.tFixStd)).str()) + "\n";
                        text += QString::fromStdString("Rate, " + (boost::format(DPF) % (results.rate)).str()) + "\n";
                    } else if (wfes::config::ConfigWfesSingle::modelType == wfes::config::ModelTypeWfesSingle::ESTABLISHMENT) {
                        text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfesSingle::starting_copies)).str()) + "\n";
                        text += QString::fromStdString("m, ") + (ConfigWfesSingle::no_rem ? "true" : "false") + "\n";
                        text += QString::fromStdString("k, " + (boost::format(DPF) % (ConfigWfesSingle::odds_ratio)).str()) + "\n";

                        // Output
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("F. est., " + (boost::format(DPF) % (results.fEst)).str()) + "\n";
                        text += QString::fromStdString("P. est., " + (boost::format(DPF) % (results.pEst)).str()) + "\n";
                        text += QString::fromStdString("T. seg., " + (boost::format(DPF) % (results.tSeg)).str()) + "\n";
                        text += QString::fromStdString("T. seg. std., " + (boost::format(DPF) % (results.tSegStd)).str()) + "\n";
                        text += QString::fromStdString("T. seg. ext., " + (boost::format(DPF) % (results.tSegExt)).str()) + "\n";
                        text += QString::fromStdString("T. seg. ext. std., " + (boost::format(DPF) % (results.tSegExtStd)).str()) + "\n";
                        text += QString::fromStdString("T. seg. fix., " + (boost::format(DPF) % (results.tSegFix)).str()) + "\n";
                        text += QString::fromStdString("T. seg. fix. std., " + (boost::format(DPF) % (results.tSegFixStd)).str()) + "\n";
                        text += QString::fromStdString("T. est., " + (boost::format(DPF) % (results.tEst)).str()) + "\n";
                        text += QString::fromStdString("T. est. std., " + (boost::format(DPF) % (results.tEstStd)).str()) + "\n";
                    } else if (wfes::config::ConfigWfesSingle::modelType == wfes::config::ModelTypeWfesSingle::EQUILIBRIUM) {
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("E[freq mut], " + (boost::format(DPF) % (results.freqMut)).str()) + "\n";
                        text += QString::fromStdString("E[freq wt], " + (boost::format(DPF) % (results.freqWt)).str()) + "\n";
                    } else if (wfes::config::ConfigWfesSingle::modelType == wfes::config::ModelTypeWfesSingle::ALLELE_AGE) {
                        text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfesSingle::starting_copies)).str()) + "\n";
                        text += QString::fromStdString("m, ") + (ConfigWfesSingle::no_rem ? "true" : "false") + "\n";
                        text += QString::fromStdString("x, " + (boost::format(DPF) % (ConfigWfesSingle::observed_copies)).str()) + "\n";

                        // Output
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("E[A], " + (boost::format(DPF) % (results.eAlleleAge)).str()) + "\n";
                        text += QString::fromStdString("S[A], " + (boost::format(DPF) % (results.sAlleleAge)).str()) + "\n";
                    }
                    clipboard->setText(text, QClipboard::Clipboard);
                    if (clipboard->supportsSelection()) {
                        clipboard->setText(text, QClipboard::Selection);
                    }

                    #if defined(Q_OS_LINUX)
                        QThread::msleep(1); //workaround for copied text not being available...
                    #endif
                }
            public slots:
                /**
                 * @brief Handle results of an execution and notify GUI that it has finished.
                 * @param results Results of an execution.
                 */
                void handleResults(ResultsWfesSingle results){
                    this->results = results;
                    this->executing = false;
                    emit results_changed();
                }

                /**
                 * @brief Handle progress of an execution and notify GUI of the progress.
                 * @param progress Progress message position in the array wfes::utils::ExecutionStatusName.
                 */
                void handleProgress(int progress){
                    this->progress = wfes::utils::ExecutionStatusName[progress];
                    emit updateProgress();
                }

            signals:
                /**
                 * @brief Signal for notifying when results have changed in backend.
                 */
                void results_changed();

                /**
                 * @brief Signal for notifying progress of an execution.
                 */
                void updateProgress();
        };
    }
}

#endif //OUTPUTCONTROLLER_H
