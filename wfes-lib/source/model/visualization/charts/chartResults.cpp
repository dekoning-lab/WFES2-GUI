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
    QLineSeries *series2 = new QLineSeries();

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
        chart->setTitle("Phase Type");

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
        chart->setTitle("Phase Type");

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

    } else if (title.compare("Wfas Dist.") == 0) {
        chart->setTitle("Wfas");

        // Append series.
        series->append(this->wfasDist);
        // Set name of series.
        series->setName("Allele frequency distribution");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxwfasDist.x());
        axisY->setMax(ChartResults::minMaxwfasDist.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Wfafle Dist.") == 0) {
        chart->setTitle("Wfafle");

        // Append series.
        series->append(this->wfafleDist);
        // Set name of series.
        series->setName("Allele frequency distribution");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxwfafleDist.x());
        axisY->setMax(ChartResults::minMaxwfafleDist.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Ext.") == 0) {
        chart->setTitle("Time Dist.");

        // Append series.
        series->append(this->timeDistExt);
        // Set name of series.
        series->setName("Probability of ext.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistExt.x());
        axisY->setMax(ChartResults::minMaxTimeDistExt.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Fix.") == 0) {
        chart->setTitle("Time Dist.");

        // Append series.
        series->append(this->timeDistFix);
        // Set name of series.
        series->setName("Probability of fix.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistFix.x());
        axisY->setMax(ChartResults::minMaxTimeDistFix.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Abs.") == 0) {
        chart->setTitle("Time Dist.");

        // Append series.
        series->append(this->timeDistAbs);
        series2->append(this->timeDistAcum);
        // Set name of series.
        series->setName("Probability of abs.");
        series2->setName("Cumulative prob. of abs.");
        // Add series.
        chart->addSeries(series);
        chart->addSeries(series2);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        series2->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistAbs.x());
        axisY->setMax(ChartResults::minMaxTimeDistAcum.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        series2->attachAxis(axisY);
    } else if (title.compare("Time Dist. SGV Sub.") == 0) {
        chart->setTitle("Time Dist. SGV");

        // Append series.
        series->append(this->timeDistSGVSub);
        // Set name of series.
        series->setName("Probability of subs.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistSGVSub.x());
        axisY->setMax(ChartResults::minMaxTimeDistSGVSub.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. SGV Acum.") == 0) {
        chart->setTitle("Time Dist. SGV");

        // Append series.
        series->append(this->timeDistSGVAcum);
        // Set name of series.
        series->setName("Cumulative prob. of subs.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistSGVAcum.x());
        axisY->setMax(ChartResults::minMaxTimeDistSGVAcum.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Skip Sub.") == 0) {
        chart->setTitle("Time Dist. Skip");

        // Append series.
        series->append(this->timeDistSkipSub);
        // Set name of series.
        series->setName("Probability of subs.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistSkipSub.x());
        axisY->setMax(ChartResults::minMaxTimeDistSkipSub.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Skip Acum.") == 0) {
        chart->setTitle("Time Dist. Skip");

        // Append series.
        series->append(this->timeDistSkipAcum);
        // Set name of series.
        series->setName("Cumulative prob. of subs.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistSkipAcum.x());
        axisY->setMax(ChartResults::minMaxTimeDistSkipAcum.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Dual Ext.") == 0) {
        chart->setTitle("Time Dist.");

        // Append series.
        series->append(this->timeDistDualExt);
        // Set name of series.
        series->setName("Probability of ext.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistDualExt.x());
        axisY->setMax(ChartResults::minMaxTimeDistDualExt.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Dual Fix.") == 0) {
        chart->setTitle("Time Dist.");

        // Append series.
        series->append(this->timeDistDualFix);
        // Set name of series.
        series->setName("Probability of fix.");
        // Add series.
        chart->addSeries(series);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistDualFix.x());
        axisY->setMax(ChartResults::minMaxTimeDistDualFix.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
    } else if (title.compare("Time Dist. Dual Abs.") == 0) {
        chart->setTitle("Time Dist.");

        // Append series.
        series->append(this->timeDistDualAbs);
        series2->append(this->timeDistDualAcum);
        // Set name of series.
        series->setName("Probability of abs.");
        series2->setName("Cumulative prob. of abs.");
        // Add series.
        chart->addSeries(series);
        chart->addSeries(series2);

        // Add axes X to chart, and attach to series.
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        series2->attachAxis(axisX);

        // Add axes Y to chart, and attach to series.
        axisY->setMin(ChartResults::minMaxTimeDistDualAbs.x());
        axisY->setMax(ChartResults::minMaxTimeDistDualAcum.y());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        series2->attachAxis(axisY);
    }

    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->font().setPointSize(12);

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
