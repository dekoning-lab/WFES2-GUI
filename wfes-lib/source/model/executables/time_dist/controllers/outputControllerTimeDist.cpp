#include "outputControllerTimeDist.h"

using namespace wfes::controllers;

OutputControllerTimeDist::OutputControllerTimeDist(QObject *parent): QObject(parent), executing(false){}

OutputControllerTimeDist::~OutputControllerTimeDist(){}

QString OutputControllerTimeDist::execute()
{
    executing = true;
    qRegisterMetaType<ResultsTimeDist>("ResultsTimeDist");

    worker = new WorkerThreadTimeDist();
    connect(worker, SIGNAL(resultReady(ResultsTimeDist)), this, SLOT(handleResults(ResultsTimeDist)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();
    return QString();
}

QString OutputControllerTimeDist::stop()
{
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerTimeDist::get_error_message() const
{
    return QString::fromStdString(wfes::config::ConfigTimeDist::error);
}

QString OutputControllerTimeDist::reset_error() const
{
    wfes::config::ConfigTimeDist::error = "";
    return QString();
}

QString OutputControllerTimeDist::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerTimeDist::get_not_exec() const
{
    return !executing;
}

QString OutputControllerTimeDist::get_progress() const
{
    return this->progress;
}
