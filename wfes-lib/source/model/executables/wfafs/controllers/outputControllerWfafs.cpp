#include "outputControllerWfafs.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerWfafs::OutputControllerWfafs(QObject *parent)
    : QObject(parent), executing(false){}

QString OutputControllerWfafs::execute() {
    ImageResults::clear();

    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsWfafs>("ResultsWfafs");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadWfafs();
    connect(worker, SIGNAL(resultReady(ResultsWfafs)), this, SLOT(handleResults(ResultsWfafs)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerWfafs::stop() {
    // This only stops the computations inside the parts of the code that test for interruption requested.
    worker->requestInterruption();
    worker->wait();

    return "";
}

QString OutputControllerWfafs::save_config() {
    ConfigWfafs::saveConfigWfafs();
    return "";
}

QString OutputControllerWfafs::load_config() {
    ConfigWfafs::loadConfigWfafs();
    return "";
}

QString OutputControllerWfafs::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerWfafs::reset_error() {
    this->results.error = "";
    return "";
}

QString OutputControllerWfafs::get_time() const {
    // Time has a special format. Only two decimal values.
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerWfafs::get_probs() const {
    // Save probs as a QStringList.
    QStringList list;
    for(int i = 0; i < this->results.probs.size(); i++) {
        // Send to GUI using DPF format.
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

bool OutputControllerWfafs::get_not_exec() const {
    return !executing;
}

QString OutputControllerWfafs::get_progress() const {
    return this->progress;
}
