#ifndef VISUALIZATIONCONTROLLER_H
#define VISUALIZATIONCONTROLLER_H

#include <QObject>
#include <wfes-lib_global.h>
#include <QQuickImageProvider>

class VisualizationImageProvider : public QQuickImageProvider
{
public:
    QList<QImage> image;
    VisualizationImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;


};

#endif // VISUALIZATIONCONTROLLER_H
