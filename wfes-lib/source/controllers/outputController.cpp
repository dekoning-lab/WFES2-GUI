#include "outputController.h"

using namespace wfes::controllers;

OutputController::OutputController(QObject* parent): QObject(parent), executing(false){}

OutputController::~OutputController()
{
    workerThread.quit();
    workerThread.wait();
}

QString OutputController::execute()
{
    executing = true;
    qRegisterMetaType<Results>("Results");

    WorkerThread *workerThread = new WorkerThread();
    connect(workerThread, SIGNAL(resultReady(Results)), this, SLOT(handleResults(Results)));
    connect(workerThread, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
    return QString();
}

QString OutputController::get_p_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results.pExt);

    if(isnan(this->results.pExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_p_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results.pFix);

    if(isnan(this->results.pFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_abs() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tAbs);

    if(isnan(this->results.tAbs))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_abs_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tAbsStd);

    if(isnan(this->results.tAbsStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tExt);

    if(isnan(this->results.tExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_ext_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tExtStd);

    if(isnan(this->results.tExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_n_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results.nExt);

    if(isnan(this->results.nExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tFix);

    if(isnan(this->results.tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_fix_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tFixStd);

    if(isnan(this->results.tFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_rate() const
{
    boost::format fmt = boost::format(DPF) % (this->results.rate);

    if(isnan(this->results.rate))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_e_freq_mut() const
{
    boost::format fmt = boost::format(DPF) % (this->results.freqMut);

    if(isnan(this->results.freqMut))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_e_freq_wt() const
{
    boost::format fmt = boost::format(DPF) % (this->results.freqWt);

    if(isnan(this->results.freqWt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_f_est() const
{
    boost::format fmt = boost::format(DPF) % (this->results.fEst);

    if(isnan(this->results.fEst))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_p_est() const
{
    boost::format fmt = boost::format(DPF) % (this->results.pEst);

    if(isnan(this->results.pEst))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_seg() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tSeg);

    if(isnan(this->results.tSeg))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_seg_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tSegStd);

    if(isnan(this->results.tSegStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_seg_est() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tSegExt);

    if(isnan(this->results.tSegExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_seg_est_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tSegExtStd);

    if(isnan(this->results.tSegExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

QString OutputController::get_t_seg_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tSegFix);

    if(isnan(this->results.tSegFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_seg_fix_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tSegFixStd);

    if(isnan(this->results.tSegFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_est() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tEst);

    if(isnan(this->results.tEst))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_est_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results.tEstStd);

    if(isnan(this->results.tEstStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_e_a() const
{
    boost::format fmt = boost::format(DPF) % (this->results.eAlleleAge);

    if(isnan(this->results.eAlleleAge))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_s_a() const
{
    boost::format fmt = boost::format(DPF) % (this->results.sAlleleAge);

    if(isnan(this->results.sAlleleAge))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_error_message() const
{
    return QString::fromStdString(wfes::config::Config::error);
}

QString OutputController::reset_error() const
{
    wfes::config::Config::error = "";
    return QString();
}

QString OutputController::get_time() const
{
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if(isnan(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputController::get_not_exec() const
{
    return !executing;
}

QString OutputController::get_progress() const
{
    qDebug() << this->progress;
    return this->progress;
}
