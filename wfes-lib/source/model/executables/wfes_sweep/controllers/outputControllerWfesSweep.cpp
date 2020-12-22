#include "outputControllerWfesSweep.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfesSweep::OutputControllerWfesSweep(QObject *parent)
    : QObject(parent), executing(false){}

QString OutputControllerWfesSweep::execute() {
    ImageResults::clear();

    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsWfesSweep>("ResultsWfesSweep");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadWfesSweep();
    connect(worker, SIGNAL(resultReady(ResultsWfesSweep)), this, SLOT(handleResults(ResultsWfesSweep)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerWfesSweep::stop() {
    // This only stops the computations inside the parts of the code that test for interruption requested.
    worker->requestInterruption();
    worker->wait();

    return "";
}

QString OutputControllerWfesSweep::save_config() {
    ConfigWfesSweep::saveConfigWfesSweep();
    return "";
}

QString OutputControllerWfesSweep::load_config() {
    ConfigWfesSweep::loadConfigWfesSweep();
    return "";
}

QString OutputControllerWfesSweep::get_t_fix() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFix);

    if((boost::math::isnan)(this->results.tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSweep::get_rate() const {
    boost::format fmt = boost::format(DPF) % (this->results.rate);

    if((boost::math::isnan)(this->results.rate))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSweep::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerWfesSweep::reset_error() {
    this->results.error = "";
    return QString();
}

QString OutputControllerWfesSweep::get_time() const {
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerWfesSweep::get_not_exec() const {
    return !executing;
}

QString OutputControllerWfesSweep::get_progress() const {
    return this->progress;
}
