#include "imageresults.h"
#include "visualizationImageProvider.h"

VisualizationImageProvider::VisualizationImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage VisualizationImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
   return ImageResults::getImage(id);
}
