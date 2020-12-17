#include "chartResults.h"

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

QList<QPointF> ChartResults::timeDistExt;
QList<QPointF> ChartResults::timeDistFix;
QList<QPointF> ChartResults::timeDistAbs;
QList<QPointF> ChartResults::timeDistAcum;
QPointF ChartResults::minMaxTimeDistExt;
QPointF ChartResults::minMaxTimeDistFix;
QPointF ChartResults::minMaxTimeDistAbs;
QPointF ChartResults::minMaxTimeDistAcum;

QList<QPointF> ChartResults::timeDistSGVSub;
QList<QPointF> ChartResults::timeDistSGVAcum;
QPointF ChartResults::minMaxTimeDistSGVSub;
QPointF ChartResults::minMaxTimeDistSGVAcum;

QList<QPointF> ChartResults::timeDistSkipSub;
QList<QPointF> ChartResults::timeDistSkipAcum;
QPointF ChartResults::minMaxTimeDistSkipSub;
QPointF ChartResults::minMaxTimeDistSkipAcum;

QList<QPointF> ChartResults::timeDistDualExt;
QList<QPointF> ChartResults::timeDistDualFix;
QList<QPointF> ChartResults::timeDistDualAbs;
QList<QPointF> ChartResults::timeDistDualAcum;
QPointF ChartResults::minMaxTimeDistDualExt;
QPointF ChartResults::minMaxTimeDistDualFix;
QPointF ChartResults::minMaxTimeDistDualAbs;
QPointF ChartResults::minMaxTimeDistDualAcum;

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
    } else if(timeDistExt.size() != 0 && name.compare("Time Dist. Ext.") == 0) {
        xySeries->replace(timeDistExt);
        return minMaxTimeDistExt;
    } else if(timeDistFix.size() != 0 && name.compare("Time Dist. Fix.") == 0) {
        xySeries->replace(timeDistFix);
        return minMaxTimeDistFix;
    } else if(timeDistAbs.size() != 0 && name.compare("Time Dist. Abs.") == 0) {
        xySeries->replace(timeDistAbs);
        return minMaxTimeDistAbs;
    } else if(timeDistAcum.size() != 0 && name.compare("Time Dist. Acum.") == 0) {
        xySeries->replace(timeDistAcum);
        return minMaxTimeDistAcum;
    } else if(timeDistSGVSub.size() != 0 && name.compare("Time Dist. SGV Sub.") == 0) {
        xySeries->replace(timeDistSGVSub);
        return minMaxTimeDistSGVSub;
    } else if(timeDistSGVAcum.size() != 0 && name.compare("Time Dist. SGV Acum.") == 0) {
        xySeries->replace(timeDistSGVAcum);
        return minMaxTimeDistSGVAcum;
    } else if(timeDistSkipSub.size() != 0 && name.compare("Time Dist. Skip Sub.") == 0) {
        xySeries->replace(timeDistSkipSub);
        return minMaxTimeDistSkipSub;
    } else if(timeDistSkipAcum.size() != 0 && name.compare("Time Dist. Skip Acum.") == 0) {
        xySeries->replace(timeDistSkipAcum);
        return minMaxTimeDistSkipAcum;
    } else if(timeDistDualExt.size() != 0 && name.compare("Time Dist. Dual Ext.") == 0) {
        xySeries->replace(timeDistDualExt);
        return minMaxTimeDistDualExt;
    } else if(timeDistDualFix.size() != 0 && name.compare("Time Dist. Dual Fix.") == 0) {
        xySeries->replace(timeDistDualFix);
        return minMaxTimeDistDualFix;
    } else if(timeDistDualAbs.size() != 0 && name.compare("Time Dist. Dual Abs.") == 0) {
        xySeries->replace(timeDistDualAbs);
        return minMaxTimeDistDualAbs;
    } else if(timeDistDualAcum.size() != 0 && name.compare("Time Dist. Dual Acum.") == 0) {
        xySeries->replace(timeDistDualAcum);
        return minMaxTimeDistDualAcum;
    } else {
        return QPointF(0, 0);
    }
}

void ChartResults::saveChartSVG(QString title, bool log, QString filePath) {
    QLineSeries *series = new QLineSeries();

    QChart *chart = new QChart();

    // Configure Axis.
    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.2e");
    QAbstractAxis *axisX;
    if(log) {
        axisX = new QLogValueAxis;
        ((QLogValueAxis*)axisX)->setMinorTickCount(0);
        ((QLogValueAxis*)axisX)->setBase(10);
        ((QLogValueAxis*)axisX)->setLabelFormat("%i");
    } else {
        axisX = new QValueAxis;
        ((QValueAxis*)axisX)->setTickCount(5);
        ((QValueAxis*)axisX)->setLabelFormat("%i");
    }

    // Depending of executable, set axis values and series.
    if(title.compare("Phase Type Dist.") == 0) {
        // Append series.
        series->append(this->phaseTypeDist);
        // Set name of series.
        series->setName("Probability of subs.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxPhaseTypeDist.x());
        axisY->setMax(ChartResults::minMaxPhaseTypeDist.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

    } else if (title.compare("Phase Type Acum.") == 0) {
        // Append series.
        series->append(this->phaseTypeDistAcum);
        // Set name of series.
        series->setName("Cumulative prob. of subs.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxPhaseTypeAcum.x());
        axisY->setMax(ChartResults::minMaxPhaseTypeAcum.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    }

    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->font().setPointSize(12);

    chart->setTitle(title);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(800, 500);

    chartView->grab();

    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(chartView->size());
    generator.setViewBox(chartView->rect());
    QPainter painter;
    painter.begin(&generator);
    chartView->render(&painter);
    painter.end();

}

void ChartResults::clearSeries(QAbstractSeries *p_series) {
    if (p_series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(p_series);
        xySeries->clear();
    }
}
