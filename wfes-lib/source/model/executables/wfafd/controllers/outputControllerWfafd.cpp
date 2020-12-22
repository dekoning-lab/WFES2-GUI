#include "outputControllerWfafd.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfafd::OutputControllerWfafd(QObject *parent)
    : QObject(parent), executing(false){}

QString OutputControllerWfafd::execute() {
    ImageResults::clear();

    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsWfafd>("ResultsWfafd");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadWfafd();
    connect(worker, SIGNAL(resultReady(ResultsWfafd)), this, SLOT(handleResults(ResultsWfafd)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerWfafd::stop() {
    // This only stops the computations inside the parts of the code that test for interruption requested.
    worker->requestInterruption();
    worker->wait();

    return "";
}

QString OutputControllerWfafd::save_config() {
    ConfigWfafd::saveConfigWfafd();
    return "";
}

QString OutputControllerWfafd::load_config() {
    ConfigWfafd::loadConfigWfafd();
    return "";
}

QString OutputControllerWfafd::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerWfafd::reset_error() {
    this->results.error = "";
    return QString();
}

QString OutputControllerWfafd::get_time() const {
    // Time has a special format. Only two decimal values.
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerWfafd::get_probs() const {
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

bool OutputControllerWfafd::get_not_exec() const {
    return !executing;
}

QString OutputControllerWfafd::get_progress() const {
    return this->progress;
}
