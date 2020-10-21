#include "outputControllerPhaseType.h"

using namespace wfes::controllers;

OutputControllerPhaseType::OutputControllerPhaseType(QObject *parent): QObject(parent), executing(false){}

OutputControllerPhaseType::~OutputControllerPhaseType() {}

QString OutputControllerPhaseType::execute()
{
    executing = true;
    qRegisterMetaType<ResultsPhaseType>("ResultsPhaseType");

    worker = new WorkerThreadPhaseType();
    connect(worker, SIGNAL(resultReady(ResultsPhaseType)), this, SLOT(handleResults(ResultsPhaseType)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();
    return QString();
}

QString OutputControllerPhaseType::stop()
{

    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerPhaseType::get_mean() const
{
    boost::format fmt = boost::format(DPF) % (this->results.mean);

    if((boost::math::isnan)(this->results.mean))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerPhaseType::get_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.std);

    if((boost::math::isnan)(this->results.std))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerPhaseType::get_error_message() const
{
    return QString::fromStdString(wfes::config::ConfigPhaseType::error);
}

QString OutputControllerPhaseType::reset_error() const
{
    wfes::config::ConfigPhaseType::error = "";
    return QString();
}

QString OutputControllerPhaseType::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerPhaseType::get_moments() const
{
    QStringList list;
    for(int i = 0; i < this->results.moments.size(); i++) {
        boost::format fmt = boost::format(DPF) % (this->results.moments(i));
        QString str = "";
        if((boost::math::isnan)(this->results.moments))
            str = "";
        else
            str = QString::fromStdString(fmt.str());
        list.append(str);
    }
    return list;
}

bool OutputControllerPhaseType::get_not_exec() const
{
    return !executing;
}

QString OutputControllerPhaseType::get_progress() const
{
    return this->progress;
}

