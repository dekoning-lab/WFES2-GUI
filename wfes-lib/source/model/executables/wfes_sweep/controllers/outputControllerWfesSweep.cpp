#include "outputControllerWfesSweep.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfesSweep::OutputControllerWfesSweep(QObject *parent): QObject(parent), executing(false){}

OutputControllerWfesSweep::~OutputControllerWfesSweep() {}

QString OutputControllerWfesSweep::execute()
{
    ImageResults::clear();

    executing = true;
    qRegisterMetaType<ResultsWfesSweep>("ResultsWfesSweep");

    worker = new WorkerThreadWfesSweep();
    connect(worker, SIGNAL(resultReady(ResultsWfesSweep)), this, SLOT(handleResults(ResultsWfesSweep)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();

    return QString();
}

QString OutputControllerWfesSweep::stop()
{
    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerWfesSweep::save_config()
{
    ConfigWfesSweep::saveConfigWfesSweep();

    return QString();
}

QString OutputControllerWfesSweep::load_config()
{
    ConfigWfesSweep::loadConfigWfesSweep();

    return QString();
}

QString OutputControllerWfesSweep::get_t_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tFix);

    if((boost::math::isnan)(this->results.tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSweep::get_rate() const
{
    boost::format fmt = boost::format(DPF) % (this->results.rate);

    if((boost::math::isnan)(this->results.rate))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSweep::get_error_message() const
{

    return QString::fromStdString(ConfigWfesSweep::error);
}

QString OutputControllerWfesSweep::reset_error() const
{
    ConfigWfesSweep::error = "";
    return QString();
}

QString OutputControllerWfesSweep::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerWfesSweep::get_not_exec() const
{
    return !executing;
}

QString OutputControllerWfesSweep::get_progress() const
{
    return this->progress;
}
