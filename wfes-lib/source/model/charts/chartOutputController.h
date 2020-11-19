#ifndef CHARTOUTPUTCONTROLLER_H
#define CHARTOUTPUTCONTROLLER_H

#include "chartResults.h"

#include <wfes-lib_global.h>

#include <boost/format.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

#include <QObject>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT ChartOutputController :public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QStringList ui_chart_probs READ get_chart_probs NOTIFY chart_changed)
            Q_PROPERTY(QStringList ui_chart_moments READ get_chart_moments NOTIFY chart_changed)


            public:
                /**
                 * @brief ChartOutputController Constructor.
                 * @param parent To be used by Qt.
                 */
                explicit ChartOutputController(QObject* parent = nullptr);

                QStringList get_chart_probs();

                QStringList get_chart_moments();

            signals:
                void chart_changed();

        };

    }
}
#endif // CHARTOUTPUTCONTROLLER_H
