﻿#ifndef OUTPUTCONTROLLERWFESSWITCHING_H
#define OUTPUTCONTROLLERWFESSWITCHING_H

#include <QApplication>
#include <QClipboard>
#include <QObject>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/wfes_switching/thread/workerThreadWfesSwitching.h>

using namespace wfes::config;

namespace wfes {
    namespace controllers {

        /**
         * @brief The OutputControllerWfesSwitching class is a controller for output parameters
         * and functions of wfes switching.
         */
        class WFESLIBSHARED_EXPORT OutputControllerWfesSwitching : public QObject{
                Q_OBJECT
                Q_PROPERTY(QString ui_execute READ execute CONSTANT)
                Q_PROPERTY(QString ui_stop READ stop CONSTANT)
                Q_PROPERTY(QString ui_save_config READ save_config CONSTANT)
                Q_PROPERTY(QString ui_load_config READ load_config CONSTANT)
                Q_PROPERTY(QString ui_get_p_ext READ get_p_ext NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_p_fix READ get_p_fix NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_t_ext READ get_t_ext NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_t_ext_std READ get_t_ext_std NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_t_fix READ get_t_fix NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_t_fix_abs_mode READ get_t_fix_abs_mode NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_t_fix_std READ get_t_fix_std NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_rate READ get_rate NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_error_message READ get_error_message NOTIFY results_changed)
                Q_PROPERTY(QString ui_reset_error READ reset_error NOTIFY results_changed)
                Q_PROPERTY(QString ui_get_time READ get_time NOTIFY results_changed)
                Q_PROPERTY(bool ui_get_not_exec READ get_not_exec NOTIFY results_changed)
                Q_PROPERTY(QString ui_progress READ get_progress NOTIFY updateProgress)

            public:

                /**
                 * @brief Results of an execution.
                 */
                ResultsWfesSwitching results;

                /**
                 * @brief Indicate if phase type if being executed.
                 */
                bool executing;

                /**
                 * @brief WorkerThread that manages the background execution of wfes sweep.
                 */
                WorkerThreadWfesSwitching* worker;

                /**
                 * @brief Message with the progress of an execution.
                 */
                QString progress = "";

                /**
                 * @brief OutputControllerWfesSwitching constructor
                 * @param parent To be used by Qt.
                 */
                OutputControllerWfesSwitching(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerWfesSwitching destructor.
                 */
                ~OutputControllerWfesSwitching() = default;

                /**
                 * @brief Execute wfes_switching and get results.
                 * @return Nothing.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of wfes_switching.
                 * @return Nothing.
                 */
                QString stop();

                /**
                 * @brief Save configuration of wfes_switching.
                 * @return Nothing.
                 */
                QString save_config();

                /**
                 * @brief Load configuration of wfes_switching.
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
                 * @brief Send t_fix to GUI.
                 * @return QString containing t_fix.
                 */
                QString get_t_fix() const;

                /**
                 * @brief Send t_fix to GUI.
                 * @return QString containing t_fix.
                 */
                QString get_t_fix_abs_mode() const;

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

                    text += QString::fromStdString("N, ");
                    for(int i = 0; i < ConfigWfesSwitching::N.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::N(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfesSwitching::N(ConfigWfesSwitching::N.size() - 1)) + "\n"));

                    text += QString::fromStdString("p, ");
                    for(int i = 0; i < ConfigWfesSwitching::p.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::p(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfesSwitching::p(ConfigWfesSwitching::p.size() - 1)) + "\n"));

                    text += QString::fromStdString("r, ");
                    for(int i = 0; i < ConfigWfesSwitching::r.size() - 1; i++) {
                        if((i + 1) % (ConfigWfesSwitching::N.size()) == 0)
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::r(i)) + " - "));
                        else
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::r(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfesSwitching::r(ConfigWfesSwitching::r.size() - 1)) + "\n"));

                    if(GlobalConfiguration::populationScaled) {
                        text += QString::fromStdString("4Nu, ");
                        for(int i = 0; i < ConfigWfesSwitching::u.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::u(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::u(ConfigWfesSwitching::u.size() - 1)) + "\n"));

                        text += QString::fromStdString("4Nv, ");
                        for(int i = 0; i < ConfigWfesSwitching::v.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::v(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::v(ConfigWfesSwitching::v.size() - 1)) + "\n"));

                        text += QString::fromStdString("2Ns, ");
                        for(int i = 0; i < ConfigWfesSwitching::s.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::s(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::s(ConfigWfesSwitching::s.size() - 1)) + "\n"));

                    } else {
                        text += QString::fromStdString("u, ");
                        for(int i = 0; i < ConfigWfesSwitching::u.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::u(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::u(ConfigWfesSwitching::u.size() - 1)) + "\n"));

                        text += QString::fromStdString("v, ");
                        for(int i = 0; i < ConfigWfesSwitching::v.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::v(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::v(ConfigWfesSwitching::v.size() - 1)) + "\n"));

                        text += QString::fromStdString("s, ");
                        for(int i = 0; i < ConfigWfesSwitching::s.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSwitching::s(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::s(ConfigWfesSwitching::s.size() - 1)) + "\n"));
                    }

                    text += QString::fromStdString("h, ");
                    for(int i = 0; i < ConfigWfesSwitching::h.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfesSwitching::h(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfesSwitching::h(ConfigWfesSwitching::h.size() - 1)) + "\n"));

                    text += QString::fromStdString("a, " + (boost::format(DPF) % (ConfigWfesSwitching::a)).str()) + "\n";

                    if(wfes::config::ConfigWfesSwitching::modelType == wfes::config::ModelTypeWfesSwitching::ABSORPTION) {
                        // Output
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("P. ext., " + (boost::format(DPF) % (results.pExt)).str()) + "\n";
                        text += QString::fromStdString("P. fix., " + (boost::format(DPF) % (results.pFix)).str()) + "\n";
                        text += QString::fromStdString("T. ext., " + (boost::format(DPF) % (results.tExt)).str()) + "\n";
                        text += QString::fromStdString("T. ext. std., " + (boost::format(DPF) % (results.tExtStd)).str()) + "\n";
                        text += QString::fromStdString("T. fix., " + (boost::format(DPF) % (results.tFixAbsMode)).str()) + "\n";
                        text += QString::fromStdString("T. fix. std., " + (boost::format(DPF) % (results.tFixStd)).str()) + "\n";
                        clipboard->setText(text, QClipboard::Clipboard);
                        if (clipboard->supportsSelection()) {
                            clipboard->setText(text, QClipboard::Selection);
                        }
                    } else if(wfes::config::ConfigWfesSwitching::modelType == wfes::config::ModelTypeWfesSwitching::FIXATION) {

                        text += QString::fromStdString("c, " + (boost::format(DPF) % (ConfigWfesSwitching::c)).str()) + "\n";

                        // Output
                        text += QString::fromStdString("Result, Value") + "\n";
                        text += QString::fromStdString("T. fix., " + (boost::format(DPF) % (results.tFix)).str()) + "\n";
                        text += QString::fromStdString("Rate, " + (boost::format(DPF) % (results.rate)).str()) + "\n";
                        clipboard->setText(text, QClipboard::Clipboard);
                        if (clipboard->supportsSelection()) {
                            clipboard->setText(text, QClipboard::Selection);
                        }
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
                void handleResults(ResultsWfesSwitching results){
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

#endif // OUTPUTCONTROLLERWFESSWITCHING_H
