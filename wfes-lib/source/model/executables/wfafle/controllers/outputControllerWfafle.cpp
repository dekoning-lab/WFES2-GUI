#include "outputControllerWfafle.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfafle::OutputControllerWfafle(QObject *parent)
    : QObject(parent), executing(false){}

QString OutputControllerWfafle::execute() {
    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsWfafle>("ResultsWfafle");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadWfafle();
    connect(worker, SIGNAL(resultReady(ResultsWfafle)), this, SLOT(handleResults(ResultsWfafle)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerWfafle::stop() {
    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return "";
}

QString OutputControllerWfafle::save_config() {
    ConfigWfafle::saveConfigWfafle();
    return "";
}

QString OutputControllerWfafle::load_config() {
    ConfigWfafle::loadConfigWfafle();
    return "";
}

QString OutputControllerWfafle::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerWfafle::reset_error() {
    this->results.error = "";
    return QString();
}

QString OutputControllerWfafle::get_time() const {
    // Time has a special format. Only two decimal values.
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerWfafle::get_probs() const {
    // Save probs as a QStringList.
    QStringList list;
    for(int i = 0; i < this->results.probs.size(); i++) {
        // Send to GUI using DPF format.
        boost::format fmt = boost::format(DPF) % (this->results.probs(i));
        QString str = "";
        if((boost::math::isnan)(this->results.probs))
            str = "";
        else
            str = QString::fromStdString(fmt.str());
        list.append(str);
    }
    return list;
}

bool OutputControllerWfafle::get_not_exec() const {
    return !executing;
}

QString OutputControllerWfafle::get_progress() const {
    return this->progress;
}
