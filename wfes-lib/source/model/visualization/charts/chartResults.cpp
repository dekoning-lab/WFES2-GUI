#include "chartResults.h"

#include <QLineSeries>

using namespace QtCharts;
using namespace wfes::controllers;

QList<QPointF> ChartResults::phaseTypeDist;
QList<QPointF> ChartResults::phaseTypeDistAcum;
QPointF ChartResults::minMaxPhaseTypeDist;
QPointF ChartResults::minMaxPhaseTypeAcum;

QList<QPointF> ChartResults::wfasDist;
QPointF ChartResults::minMaxwfasDist;

QList<QPointF> ChartResults::wfafleDist;
QPointF ChartResults::minMaxwfafleDist;

QPointF ChartResults::updateChart(QString name, QAbstractSeries *p_series) {
    QXYSeries *xySeries = static_cast<QXYSeries *>(p_series);
    if(phaseTypeDist.size() != 0 && name.compare("Phase Type Dist.") == 0) {
        xySeries->replace(phaseTypeDist);
        return minMaxPhaseTypeDist;
    } else if(phaseTypeDist.size() != 0 && name.compare("Phase Type Acum.") == 0) {
        xySeries->replace(phaseTypeDistAcum);
        return minMaxPhaseTypeAcum;
    } else if(wfasDist.size() != 0 && name.compare("Wfas Dist.") == 0) {
        xySeries->replace(wfasDist);
        return minMaxwfasDist;
    } else if(wfafleDist.size() != 0 && name.compare("Wfafle Dist.") == 0) {
        xySeries->replace(wfafleDist);
        return minMaxwfafleDist;
    } else {
        return QPointF(0, 0);
    }
}

void ChartResults::clearSeries(QAbstractSeries *p_series) {
    if (p_series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(p_series);
        xySeries->clear();
    }
}
