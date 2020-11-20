#ifndef OUTPUTCONTROLLERWFAS_H
#define OUTPUTCONTROLLERWFAS_H

#include <QObject>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include <model/executables/wfas/results/resultsWfas.h>
#include <model/executables/wfas/thread/workerThreadWfas.h>

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
