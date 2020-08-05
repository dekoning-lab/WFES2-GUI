#include "outputController.h"

using namespace wfes::controllers;

OutputController::OutputController(QObject* parent): QObject(parent){}

OutputController::~OutputController()
{
    delete results;
}

QString OutputController::execute()
{
    wfes_single single = wfes_single();
    results = single.execute();

    emit results_changed();

    return QString();
}

QString OutputController::get_p_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results->pExt);

    if(isnan(this->results->pExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_p_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results->pFix);

    if(isnan(this->results->pFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_abs() const
{
    boost::format fmt = boost::format(DPF) % (this->results->tAbs);

    if(isnan(this->results->tAbs))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_abs_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results->tAbsStd);

    if(isnan(this->results->tAbsStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results->tExt);

    if(isnan(this->results->tExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_ext_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results->tExtStd);

    if(isnan(this->results->tExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_n_ext() const
{
    boost::format fmt = boost::format(DPF) % (this->results->nExt);

    if(isnan(this->results->nExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_fix() const
{
    boost::format fmt = boost::format(DPF) % (this->results->tFix);

    if(isnan(this->results->tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputController::get_t_fix_std() const
{
    boost::format fmt = boost::format(DPF) % (this->results->tFixStd);

    if(isnan(this->results->tFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

