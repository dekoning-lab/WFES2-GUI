#ifndef OUTPUTCONTROLLERTIMEDIST_H
#define OUTPUTCONTROLLERTIMEDIST_H


#include <QObject>
#include <wfes-lib_global.h>

#include <boost/format.hpp>

#include <model/executables/time_dist/results/resultsTimeDist.h>

#include <model/executables/time_dist/thread/workerThreadTimeDist.h>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT OutputControllerTimeDist : public QObject
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

        public:

            ResultsTimeDist results;

            bool executing;

            WorkerThreadTimeDist *worker;

            QString progress = "";

            explicit OutputControllerTimeDist(QObject* parent = nullptr);

            ~OutputControllerTimeDist();

            QString execute();

            QString stop();

            /**
             * @brief Save configuration of wfes_single.
             * @return Nothing.
             */
            QString save_config();

            /**
             * @brief Load configuration of wfes_single.
             * @return Nothing.
             */
            QString load_config();

            QString get_error_message() const;

            QString reset_error();

            QString get_time() const;

            bool get_not_exec() const;

            QString get_progress() const;

        public slots:

            void handleResults(ResultsTimeDist results) {
                this->results = results;
                this->executing = false;
                emit results_changed();
            }

            void handleProgress(int progress) {
                this->progress = wfes::utils::ExecutionStatusName[progress];
                emit updateProgress();
            }

        signals:
            void results_changed();
            void operate();
            void updateProgress();
        };

    }
}

#endif // OUTPUTCONTROLLERTIMEDIST_H
