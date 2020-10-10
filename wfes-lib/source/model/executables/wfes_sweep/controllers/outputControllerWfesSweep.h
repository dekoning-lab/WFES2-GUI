#ifndef OUTPUTCONTROLLERWFESSWEEP_H
#define OUTPUTCONTROLLERWFESSWEEP_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>

#include "math.h"
#include <boost/format.hpp>

#include <model/executables/wfes_sweep/results/resultsWfesSweep.h>

#include <model/executables/wfes_sweep/thread/workerThreadWfesSweep.h>

#include <model/executables/wfes_sweep/config/configWfesSweep.h>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT OutputControllerWfesSweep: public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_execute READ execute CONSTANT)
            Q_PROPERTY(QString ui_stop READ stop CONSTANT)
            Q_PROPERTY(QString ui_get_t_fix READ get_t_fix NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_rate READ get_rate NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_error_message READ get_error_message NOTIFY results_changed)
            Q_PROPERTY(QString ui_reset_error READ reset_error NOTIFY results_changed)
            Q_PROPERTY(QString ui_get_time READ get_time NOTIFY results_changed)
            Q_PROPERTY(bool ui_get_not_exec READ get_not_exec NOTIFY results_changed)
            Q_PROPERTY(QString ui_progress READ get_progress NOTIFY updateProgress)

        public:
            ResultsWfesSweep results;

            bool executing;

            WorkerThreadWfesSweep* worker;

            QString progress = "";

            /**
             * @brief OutputControllerWfesSweep constructor
             * @param parent To be used by Qt.
             */
            OutputControllerWfesSweep(QObject* parent = nullptr);

            /**
             * @brief OutputControllerWfesSweep destructor.
             */
            ~OutputControllerWfesSweep();

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
            void handleResults(ResultsWfesSweep results){
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
#endif // OUTPUTCONTROLLERWFESSWEEP_H
