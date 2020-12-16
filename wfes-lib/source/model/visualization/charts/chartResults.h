#ifndef CHARTRESULTS_H
#define CHARTRESULTS_H

#include <QtSvg/QSvgGenerator>
#include <QAbstractSeries>
#include <QChartView>
#include <QValueAxis>
#include <QXYSeries>
#include <QObject>
#include <QBuffer>
#include <QPointF>
#include <QChart>
#include <QList>

#include <QAbstractAxis>
#include <QLineSeries>
#include <QLogValueAxis>

#include <wfes-lib_global.h>

namespace wfes {
    namespace controllers {

        /**
         * @brief The ChartResults class stores the LineSeries for be plotted in a chart.
         */
        class WFESLIBSHARED_EXPORT ChartResults : public QObject {
            Q_OBJECT

            public:
                // Phase Type Dist. lines and max/min points.
                static QList<QPointF> phaseTypeDist;
                static QList<QPointF> phaseTypeDistAcum;
                static QPointF minMaxPhaseTypeDist;
                static QPointF minMaxPhaseTypeAcum;

                // Wfas lines and max/min points.
                static QList<QPointF> wfasDist;
                static QPointF minMaxwfasDist;

                // Wfafle lines and max/min points.
                static QList<QPointF> wfafleDist;
                static QPointF minMaxwfafleDist;

                // Time Dist. lines and max/min points.
                static QList<QPointF> timeDistExt;
                static QList<QPointF> timeDistFix;
                static QList<QPointF> timeDistAbs;
                static QList<QPointF> timeDistAcum;
                static QPointF minMaxTimeDistExt;
                static QPointF minMaxTimeDistFix;
                static QPointF minMaxTimeDistAbs;
                static QPointF minMaxTimeDistAcum;

                // Time Dist. SGV lines and max/min points.
                static QList<QPointF> timeDistSGVSub;
                static QList<QPointF> timeDistSGVAcum;
                static QPointF minMaxTimeDistSGVSub;
                static QPointF minMaxTimeDistSGVAcum;

                // Time Dist. Skip lines and max/min points.
                static QList<QPointF> timeDistSkipSub;
                static QList<QPointF> timeDistSkipAcum;
                static QPointF minMaxTimeDistSkipSub;
                static QPointF minMaxTimeDistSkipAcum;

                // Time Dist. Dual lines and max/min points.
                static QList<QPointF> timeDistDualExt;
                static QList<QPointF> timeDistDualFix;
                static QList<QPointF> timeDistDualAbs;
                static QList<QPointF> timeDistDualAcum;
                static QPointF minMaxTimeDistDualExt;
                static QPointF minMaxTimeDistDualFix;
                static QPointF minMaxTimeDistDualAbs;
                static QPointF minMaxTimeDistDualAcum;

                /**
                 * @brief Default ChartResults constructor.
                 */
                ChartResults() = default;

                /**
                 * @brief Update chart in GUI.
                 * @param name Name of the requested line to update.
                 * @param p_series Series to be updated.
                 * @return Min and max value in the series.
                 */
                Q_INVOKABLE QPointF updateChart(QString name, QtCharts::QAbstractSeries *p_series);

                /**
                 * @brief Save chart as SVG image.
                 * @param title Title of the chart.
                 * @param filePath Path of the saved file.
                 */
                Q_INVOKABLE void saveChartSVG(QString title, QString filePath);

                /**
                 * @brief Clear all values in the series.
                 * @param p_series Series to be cleared.
                 */
                void clearSeries(QtCharts::QAbstractSeries *p_series);
        };
    }
}
#endif // CHARTRESULTS_H
