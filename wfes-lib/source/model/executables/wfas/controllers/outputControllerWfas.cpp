#include "outputControllerWfas.h"

using namespace wfes::controllers;

OutputControllerWfas::OutputControllerWfas(QObject *parent): QObject(parent), executing(false){}

OutputControllerWfas::~OutputControllerWfas() {}

QString OutputControllerWfas::execute()
{
    executing = true;
    qRegisterMetaType<ResultsWfas>("ResultsWfas");

    worker = new WorkerThreadWfas();
    connect(worker, SIGNAL(resultReady(ResultsWfas)), this, SLOT(handleResults(ResultsWfas)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();
    return QString();
}

QString OutputControllerWfas::stop()
{

    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerWfas::get_error_message() const
{
    return QString::fromStdString(wfes::config::ConfigWfas::error);
}

QString OutputControllerWfas::reset_error() const
{
    wfes::config::ConfigWfas::error = "";
    return QString();
}

QString OutputControllerWfas::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerWfas::get_probs() const
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

bool OutputControllerWfas::get_not_exec() const
{
    return !executing;
}

QString OutputControllerWfas::get_progress() const
{
    return this->progress;
}
