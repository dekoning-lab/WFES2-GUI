#ifndef OUTPUTCONTROLLERPHASETYPE_H
#define OUTPUTCONTROLLERPHASETYPE_H

#include <QObject>
#include <QDebug>

#include <boost/format.hpp>

#include <wfes-lib_global.h>

#include "model/executables/phase_type/thread/workerThreadPhaseType.h"

namespace wfes {
    namespace controllers {

        /**
         * @brief The OutputControllerPhaseType class is a controller for output parameters
         * and functions of phase type.
         */
        class WFESLIBSHARED_EXPORT OutputControllerPhaseType : public QObject {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
            Q_PROPERTY(QString ui_save_config READ save_config CONSTANT)
            Q_PROPERTY(QString ui_load_config READ load_config CONSTANT)
            Q_PROPERTY(QString ui_get_mean READ get_mean NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_std READ get_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_error_message READ get_error_message NOTIFY results_changed)
            Q_PROPERTY(QString ui_reset_error READ reset_error NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_time READ get_time NOTIFY results_changed)
            Q_PROPERTY(bool ui_get_not_exec READ get_not_exec NOTIFY results_changed)
            Q_PROPERTY(QString ui_progress READ get_progress NOTIFY updateProgress)
            Q_PROPERTY(QStringList ui_moments READ get_moments NOTIFY results_changed)
            Q_PROPERTY(QStringList ui_probs READ get_probs NOTIFY results_changed)

            public:
                /**
                 * @brief Results of an execution.
                 */
                ResultsPhaseType results;

                /**
                 * @brief Indicate if phase type if being executed.
                 */
                bool executing;

                /**
                 * @brief WorkerThread that manages the background execution of Phase Type.
                 */
                WorkerThreadPhaseType* worker;

                /**
                 * @brief Message with the progress of an execution.
                 */
                QString progress = "";

                /**
                 * @brief OutputControllerPhaseType Constructor
                 * @param parent To be used by Qt.
                 */
                explicit OutputControllerPhaseType(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerPhaseType Destructor.
                 */
                ~OutputControllerPhaseType() = default;

                /**
                 * @brief Execute phase type.
                 * @return Nothing.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of phase type.
                 * @return Nothing.
                 */
                QString stop();

                /**
                 * @brief Save configuration of phase type.
                 * @return Nothing.
                 */
                QString save_config();

                /**
                 * @brief Load configuration of phase type.
                 * @return Nothing.
                 */
                QString load_config();

                /**
                 * @brief Send probs to GUI.
                 * @return QStringList containing probs.
                 */
                QStringList get_probs();

                /**
                 * @brief Send mean to GUI.
                 * @return QString containing mean.
                 */
                QString get_mean() const;

                /**
                 * @brief Send std to GUI.
                 * @return QString containing std.
                 */
                QString get_std() const;

                /**
                 * @brief Send error message to GUI.
                 * @return QString containing error message.
                 */
                QString get_error_message() const;

                /**
                 * @brief Reset error message.
                 * @return Nothing.
                 */
                QString reset_error();

                /**
                 * @brief Send execution time to GUI.
                 * @return QString containing execution time.
                 */
                QString get_time() const;

                /**
                 * @brief Send moments to GUI.
                 * @return QStringList containing moments.
                 */
                QStringList get_moments() const;

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
                void handleResults(ResultsPhaseType results){
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


#endif // OUTPUTCONTROLLERPHASETYPE_H
