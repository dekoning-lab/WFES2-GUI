#ifndef OUTPUTCONTROLLERWFESSWEEP_H
#define OUTPUTCONTROLLERWFESSWEEP_H

#include <QApplication>
#include <QClipboard>
#include <QObject>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/wfes_sweep/thread/workerThreadWfesSweep.h>

using namespace wfes::config;

namespace wfes {
    namespace controllers {

        /**
         * @brief The OutputControllerWfesSweep class is a controller for output parameters
         * and functions of wfes sweep.
         */
        class WFESLIBSHARED_EXPORT OutputControllerWfesSweep: public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
            Q_PROPERTY(QString ui_save_config READ save_config CONSTANT)
            Q_PROPERTY(QString ui_load_config READ load_config CONSTANT)
            Q_PROPERTY(QString ui_get_t_fix READ get_t_fix NOTIFY results_changed)
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
            ResultsWfesSweep results;

            /**
             * @brief Indicate if phase type if being executed.
             */
            bool executing;

            /**
             * @brief WorkerThread that manages the background execution of wfes sweep.
             */
            WorkerThreadWfesSweep* worker;

            /**
             * @brief Message with the progress of an execution.
             */
            QString progress = "";

            /**
             * @brief OutputControllerWfesSweep constructor
             * @param parent To be used by Qt.
             */
            OutputControllerWfesSweep(QObject* parent = nullptr);

            /**
             * @brief OutputControllerWfesSweep destructor.
             */
            ~OutputControllerWfesSweep() = default;

            /**
             * @brief Execute wfes sweep and get results.
                 * @return Nothing.
             */
            QString execute();

            /**
             * @brief Stop an execution of wfes sweep.
             * @return Nothing.
             */
            QString stop();

            /**
             * @brief Save configuration of wfes sweep.
             * @return Nothing.
             */
            QString save_config();
            /**
             * @brief Load configuration of wfes sweep.
             * @return Nothing.
             */
            QString load_config();

            /**
             * @brief Send t_fix to GUI.
             * @return QString containing t_fix.
             */
            QString get_t_fix() const;

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
                if(wfes::config::ConfigWfesSweep::modelType == wfes::config::ModelTypeWfesSweep::FIXATION) {
                    QString text = "";
                    // Input parameters
                    text += QString::fromStdString("Parameter, Value") + "\n";
                    text += QString::fromStdString("N, " + (boost::format(DPF) % (ConfigWfesSweep::population_size)).str()) + "\n";
                    text += QString::fromStdString("a, " + (boost::format(DPF) % (ConfigWfesSweep::a)).str()) + "\n";
                    text += QString::fromStdString("c, " + (boost::format(DPF) % (ConfigWfesSweep::integration_cutoff)).str()) + "\n";
                    text += QString::fromStdString("l, " + (boost::format(DPF) % (ConfigWfesSweep::l)).str()) + "\n";
                    text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfesSweep::starting_copies)).str()) + "\n";

                    if(GlobalConfiguration::populationScaled) {
                        text += QString::fromStdString("4Nu, ");
                        for(int i = 0; i < ConfigWfesSweep::u.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSweep::u(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::u(ConfigWfesSweep::u.size() - 1)) + "\n"));

                        text += QString::fromStdString("4Nv, ");
                        for(int i = 0; i < ConfigWfesSweep::v.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSweep::v(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::v(ConfigWfesSweep::v.size() - 1)) + "\n"));

                        text += QString::fromStdString("2Ns, ");
                        for(int i = 0; i < ConfigWfesSweep::s.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSweep::s(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::s(ConfigWfesSweep::s.size() - 1)) + "\n"));

                    } else {
                        text += QString::fromStdString("u, ");
                        for(int i = 0; i < ConfigWfesSweep::u.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSweep::u(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::u(ConfigWfesSweep::u.size() - 1)) + "\n"));

                        text += QString::fromStdString("v, ");
                        for(int i = 0; i < ConfigWfesSweep::v.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSweep::v(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::v(ConfigWfesSweep::v.size() - 1)) + "\n"));

                        text += QString::fromStdString("s, ");
                        for(int i = 0; i < ConfigWfesSweep::s.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfesSweep::s(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::s(ConfigWfesSweep::s.size() - 1)) + "\n"));
                    }

                    text += QString::fromStdString("h, ");
                    for(int i = 0; i < ConfigWfesSweep::h.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfesSweep::h(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfesSweep::h(ConfigWfesSweep::h.size() - 1)) + "\n"));

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
            void handleResults(ResultsWfesSweep results){
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
#endif // OUTPUTCONTROLLERWFESSWEEP_H
