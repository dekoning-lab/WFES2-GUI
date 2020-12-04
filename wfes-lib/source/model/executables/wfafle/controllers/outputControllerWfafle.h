#ifndef OUTPUTCONTROLLERWFAFLE_H
#define OUTPUTCONTROLLERWFAFLE_H

#include <QApplication>
#include <QClipboard>
#include <QObject>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/wfafle/results/resultsWfafle.h>
#include <model/executables/wfafle/thread/workerThreadWfafle.h>

using namespace wfes::config;

namespace wfes {
    namespace controllers {

        /**
         * @brief The OutputControllerWfafle class is a controller for output parameters
         * and functions of wfafle.
         */
        class WFESLIBSHARED_EXPORT OutputControllerWfafle: public QObject {
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
            ResultsWfafle results;

            /**
             * @brief Indicate if wfafle if being executed.
             */
            bool executing;

            /**
             * @brief WorkerThread that manages the background execution of Wfafle.
             */
            WorkerThreadWfafle* worker;

            /**
             * @brief Message with the progress of an execution.
             */
            QString progress = "";

            /**
             * @brief OutputControllerWfafle constructor
             * @param parent To be used by Qt.
             */
            OutputControllerWfafle(QObject* parent = nullptr);

            /**
             * @brief OutputControllerWfafle destructor.
             */
            ~OutputControllerWfafle() = default;

            /**
             * @brief Execute wfafle and get results.
             * @return Nothing.
             */
            QString execute();

            /**
             * @brief Stop an execution of wfafle.
             * @return Nothing.
             */
            QString stop();

            /**
             * @brief Save configuration of wfafle.
             * @return Nothing.
             */
            QString save_config();

            /**
             * @brief Load configuration of wfafle.
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

        public slots:
            /**
             * @brief Handle results of an execution and notify GUI that it has finished.
             * @param results Results of an execution.
             */
            void handleResults(ResultsWfafle results){
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


            Q_INVOKABLE void coppyToClipboard() {
                QClipboard* clipboard = QApplication::clipboard();
                QString text = "";
                // Input parameters
                text += QString::fromStdString("Parameter, Value") + "\n";

                text += QString::fromStdString("N, ");
                for(int i = 0; i < ConfigWfafle::N.size() - 1; i++) {
                    text += QString::fromStdString((std::to_string(ConfigWfafle::N(i)) + "; "));
                }
                text += QString::fromStdString((std::to_string(ConfigWfafle::N(ConfigWfafle::N.size() - 1)) + "\n"));

                text += QString::fromStdString("G, ");
                for(int i = 0; i < ConfigWfafle::G.size() - 1; i++) {
                    text += QString::fromStdString((std::to_string(ConfigWfafle::G(i)) + "; "));
                }
                text += QString::fromStdString((std::to_string(ConfigWfafle::G(ConfigWfafle::G.size() - 1)) + "\n"));

                text += QString::fromStdString("s, ");
                for(int i = 0; i < ConfigWfafle::s.size() - 1; i++) {
                    text += QString::fromStdString((std::to_string(ConfigWfafle::s(i)) + "; "));
                }
                text += QString::fromStdString((std::to_string(ConfigWfafle::s(ConfigWfafle::s.size() - 1)) + "\n"));

                text += QString::fromStdString("h, ");
                for(int i = 0; i < ConfigWfafle::h.size() - 1; i++) {
                    text += QString::fromStdString((std::to_string(ConfigWfafle::h(i)) + "; "));
                }
                text += QString::fromStdString((std::to_string(ConfigWfafle::h(ConfigWfafle::h.size() - 1)) + "\n"));

                text += QString::fromStdString("u, ");
                for(int i = 0; i < ConfigWfafle::u.size() - 1; i++) {
                    text += QString::fromStdString((std::to_string(ConfigWfafle::u(i)) + "; "));
                }
                text += QString::fromStdString((std::to_string(ConfigWfafle::u(ConfigWfafle::u.size() - 1)) + "\n"));

                text += QString::fromStdString("v, ");
                for(int i = 0; i < ConfigWfafle::v.size() - 1; i++) {
                    text += QString::fromStdString((std::to_string(ConfigWfafle::v(i)) + "; "));
                }
                text += QString::fromStdString((std::to_string(ConfigWfafle::v(ConfigWfafle::v.size() - 1)) + "\n"));

                text += QString::fromStdString("a, " + (boost::format(DPF) % (ConfigWfafle::a)).str()) + "\n";
                text += QString::fromStdString("p, " + (boost::format(DPF) % (ConfigWfafle::p)).str()) + "\n";


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
#endif // OUTPUTCONTROLLERWFAFLE_H
