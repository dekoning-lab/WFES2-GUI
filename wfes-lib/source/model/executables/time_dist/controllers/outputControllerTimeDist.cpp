#include "outputControllerTimeDist.h"

using namespace wfes::controllers;
using namespace wfes::config;

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

QString OutputControllerTimeDist::save_config()
{
    ConfigTimeDist::saveConfigTimeDist();
    ConfigTimeDistSGV::saveConfigTimeDistSGV();

    return QString();
}

QString OutputControllerTimeDist::load_config()
{
    ConfigTimeDist::loadConfigTimeDist();
    ConfigTimeDistSGV::loadConfigTimeDistSGV();

    return QString();

}

QStringList OutputControllerTimeDist::get_probs() {
    QStringList list;
    QString str = "";
    for(int i = 0; i < this->results.probs.rows(); i++) {
        for(int j = 0; j < this->results.probs.cols(); j++) {

            boost::format fmt = boost::format(DPF) % (this->results.probs(i, j));
            if((boost::math::isnan)(this->results.probs))
                str += "";
            else {
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

QString OutputControllerTimeDist::get_error_message() const
{
    return QString::fromStdString(this->results.error);
}

QString OutputControllerTimeDist::reset_error()
{
    this->results.error = "";
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
