﻿#include "outputControllerWfesSingle.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfesSingle::OutputControllerWfesSingle(QObject* parent)
    : QObject(parent), executing(false){}

QString OutputControllerWfesSingle::execute() {
    ImageResults::clear();

    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsWfesSingle>("ResultsWfesSingle");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadWfesSingle();
    connect(worker, SIGNAL(resultReady(ResultsWfesSingle)), this, SLOT(handleResults(ResultsWfesSingle)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerWfesSingle::stop() {
    // This only stops the computations inside the parts of the code that test for interruption requested.
    worker->requestInterruption();
    worker->wait();

    return "";
}

QString OutputControllerWfesSingle::save_config() {
    ConfigWfesSingle::saveConfigWfesSingle();
    return "";
}

QString OutputControllerWfesSingle::load_config() {
    ConfigWfesSingle::loadConfigWfesSingle();
    return "";
}

QString OutputControllerWfesSingle::get_p_ext() const {
    boost::format fmt = boost::format(DPF) % (this->results.pExt);

    if((boost::math::isnan)(this->results.pExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_p_fix() const {
    boost::format fmt = boost::format(DPF) % (this->results.pFix);

    if((boost::math::isnan)(this->results.pFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_abs() const {
    boost::format fmt = boost::format(DPF) % (this->results.tAbs);

    if((boost::math::isnan)(this->results.tAbs))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_abs_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tAbsStd);

    if((boost::math::isnan)(this->results.tAbsStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_ext() const {
    boost::format fmt = boost::format(DPF) % (this->results.tExt);

    if((boost::math::isnan)(this->results.tExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_ext_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tExtStd);

    if((boost::math::isnan)(this->results.tExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_n_ext() const {
    boost::format fmt = boost::format(DPF) % (this->results.nExt);

    if((boost::math::isnan)(this->results.nExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_fix() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFix);

    if((boost::math::isnan)(this->results.tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_fix_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFixStd);

    if((boost::math::isnan)(this->results.tFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_fix_abs_mode() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFixAbsMode);

    if((boost::math::isnan)(this->results.tFixAbsMode))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_fix_std_abs_mode() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFixStdAbsMode);

    if((boost::math::isnan)(this->results.tFixStdAbsMode))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_rate() const {
    boost::format fmt = boost::format(DPF) % (this->results.rate);

    if((boost::math::isnan)(this->results.rate))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_e_freq_mut() const {
    boost::format fmt = boost::format(DPF) % (this->results.freqMut);

    if((boost::math::isnan)(this->results.freqMut))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_e_freq_wt() const {
    boost::format fmt = boost::format(DPF) % (this->results.freqWt);

    if((boost::math::isnan)(this->results.freqWt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_f_est() const {
    boost::format fmt = boost::format(DPF) % (this->results.fEst);

    if((boost::math::isnan)(this->results.fEst))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_p_est() const {
    boost::format fmt = boost::format(DPF) % (this->results.pEst);

    if((boost::math::isnan)(this->results.pEst))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_seg() const {
    boost::format fmt = boost::format(DPF) % (this->results.tSeg);

    if((boost::math::isnan)(this->results.tSeg))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_seg_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tSegStd);

    if((boost::math::isnan)(this->results.tSegStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_seg_est() const {
    boost::format fmt = boost::format(DPF) % (this->results.tSegExt);

    if((boost::math::isnan)(this->results.tSegExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_seg_est_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tSegExtStd);

    if((boost::math::isnan)(this->results.tSegExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

QString OutputControllerWfesSingle::get_t_seg_fix() const {
    boost::format fmt = boost::format(DPF) % (this->results.tSegFix);

    if((boost::math::isnan)(this->results.tSegFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_seg_fix_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tSegFixStd);

    if((boost::math::isnan)(this->results.tSegFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_est() const {
    boost::format fmt = boost::format(DPF) % (this->results.tEst);

    if((boost::math::isnan)(this->results.tEst))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_t_est_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tEstStd);

    if((boost::math::isnan)(this->results.tEstStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_e_a() const {
    boost::format fmt = boost::format(DPF) % (this->results.eAlleleAge);

    if((boost::math::isnan)(this->results.eAlleleAge))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_s_a() const {
    boost::format fmt = boost::format(DPF) % (this->results.sAlleleAge);

    if((boost::math::isnan)(this->results.sAlleleAge))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSingle::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerWfesSingle::reset_error() {
    this->results.error = "";
    return QString();
}

QString OutputControllerWfesSingle::get_time() const {
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerWfesSingle::get_not_exec() const {
    return !executing;
}

QString OutputControllerWfesSingle::get_progress() const {
    return this->progress;
}
