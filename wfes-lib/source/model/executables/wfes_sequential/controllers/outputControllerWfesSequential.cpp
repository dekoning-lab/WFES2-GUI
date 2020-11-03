#include "outputControllerWfesSequential.h"

using namespace wfes::controllers;

OutputControllerWfesSequential::OutputControllerWfesSequential(QObject* parent): QObject(parent), executing(false){}

OutputControllerWfesSequential::~OutputControllerWfesSequential() {}

QString OutputControllerWfesSequential::execute()
{
    ImageResults::clear();

    executing = true;
    qRegisterMetaType<ResultsWfesSequential>("ResultsWfesSequential");

    worker = new WorkerThreadWfesSequential();
    connect(worker, SIGNAL(resultReady(ResultsWfesSequential)), this, SLOT(handleResults(ResultsWfesSequential)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    worker->start();
    return QString();
}

QString OutputControllerWfesSequential::stop()
{
    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerWfesSequential::get_p_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results.pExt);

    if((boost::math::isnan)(this->results.pExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_p_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results.pFix);

    if((boost::math::isnan)(this->results.pFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_p_tmo() const
{
    boost::format fmt = boost::format(DPF) % (this->results.pTmo);

    if((boost::math::isnan)(this->results.pTmo))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_t_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tExt);

    if((boost::math::isnan)(this->results.tExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_t_ext_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tExtStd);

    if((boost::math::isnan)(this->results.tExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_t_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tFix);

    if((boost::math::isnan)(this->results.tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_t_fix_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tFixStd);

    if((boost::math::isnan)(this->results.tFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_t_tmo() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tTmo);

    if((boost::math::isnan)(this->results.tTmo))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_t_tmo_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tTmoStd);

    if((boost::math::isnan)(this->results.tTmoStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSequential::get_error_message() const
{
    return QString::fromStdString(wfes::config::ConfigWfesSequential::error);
}

QString OutputControllerWfesSequential::reset_error() const
{
    wfes::config::ConfigWfesSequential::error = "";
    return QString();
}

QString OutputControllerWfesSequential::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerWfesSequential::get_not_exec() const
{
    return !executing;
}

QString OutputControllerWfesSequential::get_progress() const
{
    return this->progress;
}
