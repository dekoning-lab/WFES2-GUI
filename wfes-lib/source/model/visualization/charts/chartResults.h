#ifndef CHARTRESULTS_H
#define CHARTRESULTS_H

#include <QAbstractSeries>
#include <QXYSeries>
#include <QObject>
#include <QPointF>
#include <QList>

#include <wfes-lib_global.h>

namespace wfes {
    namespace controllers {
        class WFESLIBSHARED_EXPORT ChartResults :public QObject {
            Q_OBJECT

            public:
                static QList<QPointF> phaseTypeDist;
                static QList<QPointF> phaseTypeDistAcum;
                static QPointF minMaxPhaseTypeDist;
                static QPointF minMaxPhaseTypeAcum;

                static QList<QPointF> wfasDist;
                static QPointF minMaxwfasDist;

                static QList<QPointF> wfafleDist;
                static QPointF minMaxwfafleDist;

                ChartResults() = default;

                Q_INVOKABLE QPointF updateChart(QString name, QtCharts::QAbstractSeries *p_series);

                void clearSeries(QtCharts::QAbstractSeries *p_series);
        };
    }
}
#endif // CHARTRESULTS_H
