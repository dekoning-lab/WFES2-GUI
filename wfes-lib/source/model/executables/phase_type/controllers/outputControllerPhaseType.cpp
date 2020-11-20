#include "outputControllerPhaseType.h"

using namespace wfes::controllers;
using namespace wfes::config;

OutputControllerPhaseType::OutputControllerPhaseType(QObject *parent)
    : QObject(parent), executing(false) {}

QString OutputControllerPhaseType::execute() {
    // Set executing to true.
    executing = true;

    // Register results class as metatype, so it can be passed between Q_OBJECTS as slot.
    qRegisterMetaType<ResultsPhaseType>("ResultsPhaseType");

    // Instantiate worker and connect signals of this controller with the worker.
    worker = new WorkerThreadPhaseType();
    connect(worker, SIGNAL(resultReady(ResultsPhaseType)), this, SLOT(handleResults(ResultsPhaseType)));
    connect(worker, SIGNAL(updateProgress(int)), this, SLOT(handleProgress(int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

    // Start execution.
    worker->start();

    return "";
}

QString OutputControllerPhaseType::stop() {
    // TODO Looks that using terminate is a bad practice because it can stop the thread, for example, while writting a file,
    // and the file will be corrupt then. Look for a better way of doing this.
    worker->terminate();
    worker->wait();
    worker->exit();

    return "";
}

QString OutputControllerPhaseType::save_config() {
    ConfigPhaseType::saveConfigPhaseType();
    return "";
}

QString OutputControllerPhaseType::load_config() {
    ConfigPhaseType::loadConfigPhaseType();
    return "";
}

QStringList OutputControllerPhaseType::get_probs() {
    // Save probs as a QStringList.
    // Each element of the QStringList is a row of probs.
    QStringList list;
    QString str = "";
    for(int i = 0; i < this->results.probs.rows(); i++) {
        for(int j = 0; j < this->results.probs.cols(); j++) {
            // Send to GUI using DPF format.
            boost::format fmt = boost::format(DPF) % (this->results.probs(i, j));
            if((boost::math::isnan)(this->results.probs))
                str += "";
            else {
                // Concatenate using ', '. The last one does not need it.
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

QString OutputControllerPhaseType::get_mean() const {
    boost::format fmt = boost::format(DPF) % (this->results.mean);

    if((boost::math::isnan)(this->results.mean))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerPhaseType::get_std() const {
    boost::format fmt = boost::format(DPF) % (this->results.std);

    if((boost::math::isnan)(this->results.std))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QString OutputControllerPhaseType::get_error_message() const {
    return QString::fromStdString(this->results.error);
}

QString OutputControllerPhaseType::reset_error() {
    this->results.error = "";
    return "";
}

QString OutputControllerPhaseType::get_time() const {
    // Time has a special format. Only two decimal values.
    boost::format fmt = boost::format("%1$.2f") % (this->results.time);

    if((boost::math::isnan)(this->results.time))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

QStringList OutputControllerPhaseType::get_moments() const {
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

bool OutputControllerPhaseType::get_not_exec() const {
    return !executing;
}

QString OutputControllerPhaseType::get_progress() const {
    return this->progress;
}

