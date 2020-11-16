#ifndef OUTPUTCONTROLLERWFAS_H
#define OUTPUTCONTROLLERWFAS_H

#include <QObject>
#include <QDebug>
#include <wfes-lib_global.h>

#include "math.h"
#include <boost/format.hpp>

#include <model/executables/wfas/results/resultsWfas.h>

#include <model/executables/wfas/thread/workerThreadWfas.h>

#include <model/executables/wfas/config/configWfas.h>

#include <model/visualization/imageresults.h>

namespace wfes {
    namespace controllers {

    class WFESLIBSHARED_EXPORT OutputControllerWfas: public QObject
    {
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
        ResultsWfas results;

        bool executing;

        WorkerThreadWfas* worker;

        QString progress = "";

        /**
         * @brief OutputControllerWfesSweep constructor
         * @param parent To be used by Qt.
         */
        OutputControllerWfas(QObject* parent = nullptr);

        /**
         * @brief OutputControllerWfesSweep destructor.
         */
        ~OutputControllerWfas();

        /**
         * @brief Execute wfas and get results.
         * @return Results of wfas execution.
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

        QString get_progress() const;

    public slots:
        void handleResults(ResultsWfas results){
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
#endif // OUTPUTCONTROLLERWFAS_H
