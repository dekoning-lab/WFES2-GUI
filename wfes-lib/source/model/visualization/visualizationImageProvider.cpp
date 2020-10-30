
#include "visualizationImageProvider.h"

VisualizationImageProvider::VisualizationImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage VisualizationImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
   QImage scaled = ImageResults::getImage(id.split("?")[0]).scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);

   return scaled;
}
