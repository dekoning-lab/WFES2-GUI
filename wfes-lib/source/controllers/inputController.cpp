#include "inputController.h"

using namespace wfes::controllers;

InputController::InputController(QObject* parent): QObject(parent){
    emit input_changed();
}

InputController::~InputController(){}

QString InputController::get_n() const
{
    boost::format fmt = boost::format(DPF) % (wfes::config::Config::population_size);

    if(isnan(wfes::config::Config::population_size))
        return "Error";
    else
        return QString::fromStdString(fmt.str());
}

void InputController::set_n(QString n) const
{
    std::string n_str = n.toStdString();
    double n_d = boost::lexical_cast<double>(n_str);
    wfes::config::Config::population_size = n_d;
}


