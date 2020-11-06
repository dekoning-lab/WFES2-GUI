#include "outputControllerWfafle.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfafle::OutputControllerWfafle(QObject *parent): QObject(parent), executing(false){}

OutputControllerWfafle::~OutputControllerWfafle() {}

QString OutputControllerWfafle::execute()
{
    executing = true;
    qRegisterMetaType<ResultsWfafle>("ResultsWfafle");

    worker = new WorkerThreadWfafle();
    connect(worker, SIGNAL(resultReady(ResultsWfafle)), this, SLOT(handleResults(ResultsWfafle)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();
    return QString();
}

QString OutputControllerWfafle::stop()
{

    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerWfafle::save_config()
{
    ConfigWfafle::saveConfigWfafle();

    return QString();
}

QString OutputControllerWfafle::load_config()
{
    ConfigWfafle::loadConfigWfafle();

    return QString();
}

QString OutputControllerWfafle::get_error_message() const
{
    return QString::fromStdString(wfes::config::ConfigWfafle::error);
}

QString OutputControllerWfafle::reset_error() const
{
    wfes::config::ConfigWfafle::error = "";
    return QString();
}

QString OutputControllerWfafle::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerWfafle::get_probs() const
{
    QStringList list;
    for(int i = 0; i < this->results.probs.size(); i++) {
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

bool OutputControllerWfafle::get_not_exec() const
{
    return !executing;
}

QString OutputControllerWfafle::get_progress() const
{
    return this->progress;
}
