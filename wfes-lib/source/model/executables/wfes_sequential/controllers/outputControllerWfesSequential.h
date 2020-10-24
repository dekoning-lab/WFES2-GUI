#ifndef OUTPUTCONTROLLERWFESSEQUENTIAL_H
#define OUTPUTCONTROLLERWFESSEQUENTIAL_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>

#include "math.h"
#include <boost/format.hpp>

#include <model/executables/wfes_sequential/results/resultsWfesSequential.h>

#include <model/executables/wfes_sequential/thread/workerThreadWfesSequential.h>

#include <model/executables/wfes_sequential/config/configWfesSequential.h>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT OutputControllerWfesSequential : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
            Q_PROPERTY(QString ui_get_p_ext READ get_p_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_p_fix READ get_p_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_p_tmo READ get_p_tmo NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_ext READ get_t_ext NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_ext_std READ get_t_ext_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix READ get_t_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_fix_std READ get_t_fix_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_tmo READ get_t_tmo NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_t_tmo_std READ get_t_tmo_std NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_error_message READ get_error_message NOTIFY results_changed)
            Q_PROPERTY(QString ui_reset_error READ reset_error NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_time READ get_time NOTIFY results_changed)
            Q_PROPERTY(bool ui_get_not_exec READ get_not_exec NOTIFY results_changed)
            Q_PROPERTY(QString ui_progress READ get_progress NOTIFY updateProgress)

            public:
                ResultsWfesSequential results;

                bool executing;

                WorkerThreadWfesSequential* worker;

                QString progress = "";

                /**
                 * @brief OutputControllerWfesSequential constructor
                 * @param parent To be used by Qt.
                 */
                OutputControllerWfesSequential(QObject* parent = nullptr);

                /**
                 * @brief OutputControllerWfesSequential destructor.
                 */
                ~OutputControllerWfesSequential();

                /**
                 * @brief Execute wfes_sequential and get results.
                 * @return Results of wfes_sequential execution.
                 */
                QString execute();

                /**
                 * @brief Stop an execution of wfes_sequential.
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
                 * @brief Send p_tmo to GUI.
                 * @return QString containing p_tmo.
                 */
                QString get_p_tmo() const;

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
                 * @brief Send t_fix_std to GUI.
                 * @return QString containing t_fix_std.
                 */
                QString get_t_fix_std() const;

                /**
                 * @brief Send t_tmo to GUI.
                 * @return QString containing t_tmo.
                 */
                QString get_t_tmo() const;

                /**
                 * @brief Send t_tmo_std to GUI.
                 * @return QString containing t_tmo_std.
                 */
                QString get_t_tmo_std() const;

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
                void handleResults(ResultsWfesSequential results){
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
#endif // OUTPUTCONTROLLERWFESSEQUENTIAL_H
