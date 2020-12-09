#ifndef OUTPUTCONTROLLERWFAS_H
#define OUTPUTCONTROLLERWFAS_H

#include <QApplication>
#include <QClipboard>
#include <QObject>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/wfas/results/resultsWfas.h>
#include <model/executables/wfas/thread/workerThreadWfas.h>

using namespace wfes::config;

namespace wfes {
    namespace controllers {

        /**
         * @brief The OutputControllerWfas class is a controller for output parameters
         * and functions of wfas.
         */
        class WFESLIBSHARED_EXPORT OutputControllerWfas: public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
            Q_PROPERTY(QString ui_save_config READ save_config CONSTANT)
            Q_PROPERTY(QString ui_load_config READ load_config CONSTANT)
            Q_PROPERTY(QString ui_get_error_message READ get_error_message NOTIFY results_changed)
            Q_PROPERTY(QString ui_reset_error READ reset_error NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_time READ get_time NOTIFY results_changed)
            Q_PROPERTY(bool ui_get_not_exec READ get_not_exec NOTIFY results_changed)
            Q_PROPERTY(QString ui_progress READ get_progress NOTIFY updateProgress)
            Q_PROPERTY(QStringList ui_probs READ get_probs NOTIFY results_changed)

            public:
                /**
                 * @brief Results of an execution.
                 */
                ResultsWfas results;

                /**
                 * @brief Indicate if wfas if being executed.
                 */
                bool executing;

                /**
                 * @brief WorkerThread that manages the background execution of Wfas.
                 */
                WorkerThreadWfas* worker;

                /**
                 * @brief Message with the progress of an execution.
                 */
                QString progress = "";

                /**
                 * @brief OutputControllerWfas constructor
                 * @param parent To be used by Qt.
                 */
                OutputControllerWfas(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerWfesSweep destructor.
                 */
                ~OutputControllerWfas() = default;

                /**
                 * @brief Execute wfas and get results.
                 * @return Nothing.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of wfas.
                 * @return Nothing.
                 */
                QString stop();

                /**
                 * @brief Save configuration of wfas.
                 * @return Nothing.
                 */
                QString save_config();

                /**
                 * @brief Load configuration of wfas.
                 * @return Nothing.
                 */
                QString load_config();

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
                 * @brief Send prob. dist. to GUI.
                 * @return  QList containing prob. dist.
                 */
                QStringList get_probs() const;

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
                    for(int i = 0; i < ConfigWfas::N.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfas::N(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfas::N(ConfigWfas::N.size() - 1)) + "\n"));

                    text += QString::fromStdString("G, ");
                    for(int i = 0; i < ConfigWfas::G.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfas::G(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfas::G(ConfigWfas::G.size() - 1)) + "\n"));

                    text += QString::fromStdString("F, ");
                    for(int i = 0; i < ConfigWfas::f.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfas::f(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfas::G(ConfigWfas::G.size() - 1)) + "\n"));

                    if(GlobalConfiguration::populationScaled) {
                        text += QString::fromStdString("4Nu, ");
                        for(int i = 0; i < ConfigWfas::u.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfas::u(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfas::u(ConfigWfas::u.size() - 1)) + "\n"));

                        text += QString::fromStdString("4Nv, ");
                        for(int i = 0; i < ConfigWfas::v.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfas::v(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfas::v(ConfigWfas::v.size() - 1)) + "\n"));

                        text += QString::fromStdString("2Ns, ");
                        for(int i = 0; i < ConfigWfas::s.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfas::s(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfas::s(ConfigWfas::s.size() - 1)) + "\n"));

                    } else {
                        text += QString::fromStdString("u, ");
                        for(int i = 0; i < ConfigWfas::u.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfas::u(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfas::u(ConfigWfas::u.size() - 1)) + "\n"));

                        text += QString::fromStdString("v, ");
                        for(int i = 0; i < ConfigWfas::v.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfas::v(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfas::v(ConfigWfas::v.size() - 1)) + "\n"));

                        text += QString::fromStdString("s, ");
                        for(int i = 0; i < ConfigWfas::s.size() - 1; i++) {
                            text += QString::fromStdString((std::to_string(ConfigWfas::s(i)) + "; "));
                        }
                        text += QString::fromStdString((std::to_string(ConfigWfas::s(ConfigWfas::s.size() - 1)) + "\n"));
                    }

                    text += QString::fromStdString("h, ");
                    for(int i = 0; i < ConfigWfas::h.size() - 1; i++) {
                        text += QString::fromStdString((std::to_string(ConfigWfas::h(i)) + "; "));
                    }
                    text += QString::fromStdString((std::to_string(ConfigWfas::h(ConfigWfas::h.size() - 1)) + "\n"));

                    text += QString::fromStdString("a, " + (boost::format(DPF) % (ConfigWfas::a)).str()) + "\n";
                    text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfas::p)).str()) + "\n";
                    text += QString::fromStdString("No proj, ") + (ConfigWfas::no_proj ? "true" : "false") + "\n";

                    text += QString::fromStdString("Allele freq. dist.\n");
                    for(int i = 0; i < results.probs.size(); i++) {
                        text += QString::fromStdString((boost::format(DPF) % (results.probs[i])).str()) + "\n";
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
                void handleResults(ResultsWfas results){
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
#endif // OUTPUTCONTROLLERWFAS_H
