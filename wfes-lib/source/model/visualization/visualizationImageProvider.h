#ifndef VISUALIZATIONCONTROLLER_H
#define VISUALIZATIONCONTROLLER_H

#include <wfes-lib_global.h>
#include <QQuickImageProvider>
#include "imageOutputController.h"
#include "imageresults.h"

class VisualizationImageProvider : public QQuickImageProvider
{
    public:

        VisualizationImageProvider();

        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

};

#endif // VISUALIZATIONCONTROLLER_H
