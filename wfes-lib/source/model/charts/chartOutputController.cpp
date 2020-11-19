#include "chartOutputController.h"

using namespace wfes::controllers;

ChartOutputController::ChartOutputController(QObject *parent) : QObject(parent){}

QStringList ChartOutputController::get_chart_probs()
{
    QStringList list;
    for(int i = 0; i < ChartResults::probabilities.size(); i++) {
        boost::format fmt = boost::format(DPF) % (ChartResults::probabilities(i));
        QString str = "";
        if((boost::math::isnan)(ChartResults::probabilities))
            str = "";
        else
            str = QString::fromStdString(fmt.str());
        list.append(str);
    }
    return list;
}

QStringList ChartOutputController::get_chart_moments()
{
    QStringList list;
    for(int i = 0; i < ChartResults::moments.size(); i++) {
        boost::format fmt = boost::format(DPF) % (ChartResults::moments(i));
        QString str = "";
        if((boost::math::isnan)(ChartResults::moments))
            str = "";
        else
            str = QString::fromStdString(fmt.str());
        list.append(str);
    }
    return list;
}
