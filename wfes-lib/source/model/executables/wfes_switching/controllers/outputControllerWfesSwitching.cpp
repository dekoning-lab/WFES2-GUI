#include "outputControllerWfesSwitching.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfesSwitching::OutputControllerWfesSwitching(QObject* parent)
    : QObject(parent), executing(false){}

QString OutputControllerWfesSwitching::execute() {
    ImageResults::clear();

    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsWfesSwitching>("ResultsWfesSwitching");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadWfesSwitching();
    connect(worker, SIGNAL(resultReady(ResultsWfesSwitching)), this, SLOT(handleResults(ResultsWfesSwitching)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerWfesSwitching::stop() {
    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return QString();
}

QString OutputControllerWfesSwitching::save_config() {
    ConfigWfesSwitching::saveConfigWfesSwitching();
    return "";
}

QString OutputControllerWfesSwitching::load_config() {
    ConfigWfesSwitching::loadConfigWfesSwitching();
    return "";
}

QString OutputControllerWfesSwitching::get_p_ext() const {
    boost::format fmt = boost::format(DPF) % (this->results.pExt);

     if((boost::math::isnan)(this->results.pExt))
         return "";
     else
         return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSwitching::get_p_fix() const {
    boost::format fmt = boost::format(DPF) % (this->results.pFix);

    if((boost::math::isnan)(this->results.pFix))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

QString OutputControllerWfesSwitching::get_t_ext() const {
    boost::format fmt = boost::format(DPF) % (this->results.tExt);

    if((boost::math::isnan)(this->results.tExt))
        return "";
    else
        return QString::fromStdString(fmt.str());

}

QString OutputControllerWfesSwitching::get_t_ext_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tExtStd);

    if((boost::math::isnan)(this->results.tExtStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSwitching::get_t_fix() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFix);

    if((boost::math::isnan)(this->results.tFix))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSwitching::get_t_fix_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.tFixStd);

    if((boost::math::isnan)(this->results.tFixStd))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSwitching::get_rate() const {
    boost::format fmt = boost::format(DPF) % (this->results.rate);

    if((boost::math::isnan)(this->results.rate))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerWfesSwitching::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerWfesSwitching::reset_error() {
    this->results.error = "";
    return QString();
}

QString OutputControllerWfesSwitching::get_time() const {
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

bool OutputControllerWfesSwitching::get_not_exec() const {
    return !executing;
}

QString OutputControllerWfesSwitching::get_progress() const {
    return this->progress;
}
