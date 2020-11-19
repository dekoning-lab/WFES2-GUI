#ifndef OUTPUTCONTROLLERPHASETYPE_H
#define OUTPUTCONTROLLERPHASETYPE_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>

#include <model/executables/phase_type/thread/workerThreadPhaseType.h>

#include <boost/format.hpp>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT OutputControllerPhaseType : public QObject
        {
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

                ResultsPhaseType results;

                bool executing;

                WorkerThreadPhaseType* worker;

                QString progress = "";

                /**
                 * @brief OutputControllerPhaseType constructor
                 * @param parent To be used by Qt.
                 */
                explicit OutputControllerPhaseType(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerPhaseType Destructor.
                 */
                ~OutputControllerPhaseType();

                /**
                 * @brief Execute phase_type and get results.
                 * @return Results of wfes_single execution.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of phase_type.
                 * @return Nothing.
                 */
                QString stop();

                /**
                 * @brief Save configuration of phase_type.
                 * @return Nothing.
                 */
                QString save_config();

                /**
                 * @brief Load configuration of phase_type.
                 * @return Nothing.
                 */
                QString load_config();

                QStringList get_probs();

                /**
                 * @brief Send get_mean to GUI.
                 * @return QString containing get_mean.
                 */
                QString get_mean() const;

                /**
                 * @brief Send std to GUI.
                 * @return QString containing std.
                 */
                QString get_std() const;

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
                 * @brief Send moments to GUI.
                 * @return  QList containing moments.
                 */
                QStringList get_moments() const;

                /**
                 * @brief Send if the background thread is executing.
                 * @return Boolean telling if the background thread is executing.
                 */
                bool get_not_exec() const;

                QString get_progress() const;

            public slots:
                void handleResults(ResultsPhaseType results){
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


#endif // OUTPUTCONTROLLERPHASETYPE_H
