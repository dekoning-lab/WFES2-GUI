#include "outputControllerTimeDist.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerTimeDist::OutputControllerTimeDist(QObject *parent)
    : QObject(parent), executing(false){}

QString OutputControllerTimeDist::execute() {
    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsTimeDist>("ResultsTimeDist");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadTimeDist();
    connect(worker, SIGNAL(resultReady(ResultsTimeDist)), this, SLOT(handleResults(ResultsTimeDist)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerTimeDist::stop() {
    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return "";
}

QString OutputControllerTimeDist::save_config() {
    ConfigTimeDist::saveConfigTimeDist();
    ConfigTimeDistSGV::saveConfigTimeDistSGV();
    return "";
}

QString OutputControllerTimeDist::load_config() {
    ConfigTimeDist::loadConfigTimeDist();
    ConfigTimeDistSGV::loadConfigTimeDistSGV();
    return "";

}

QStringList OutputControllerTimeDist::get_probs() {
    // Save probs as a QStringList.
    // Each element of the QStringList is a row of probs.
    QStringList list;
    QString str = "";
    for(int i = 0; i < this->results.probs.rows(); i++) {
        for(int j = 0; j < this->results.probs.cols(); j++) {
            // Send to GUI using DPF format.
            boost::format fmt = boost::format(DPF) % (this->results.probs(i, j));
            if((boost::math::isnan)(this->results.probs))
                str += "";
            else {
                // Concatenate using ', '. The last one does not need it.
                if(j != this->results.probs.cols()-1)
                    str += QString::fromStdString(fmt.str()) + ", ";
                else
                    str += QString::fromStdString(fmt.str());
            }
        }
        list.append(str);
        str = "";
    }
    return list;
}

QString OutputControllerTimeDist::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerTimeDist::reset_error() {
    this->results.error = "";
    return "";
}

QString OutputControllerTimeDist::get_time() const {
    // Time has a special format. Only two decimal values.
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerTimeDist::get_not_exec() const {
    return !executing;
}

QString OutputControllerTimeDist::get_progress() const {
    return this->progress;
}
