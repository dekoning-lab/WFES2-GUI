#ifndef VISUALIZATIONCONTROLLER_H
#define VISUALIZATIONCONTROLLER_H

#include <wfes-lib_global.h>
#include <QQuickImageProvider>
#include "imageOutputController.h"
#include "imageresults.h"

/**
 * @brief The VisualizationImageProvider class provides images to GUI.
 */
class  WFESLIBSHARED_EXPORT VisualizationImageProvider : public QQuickImageProvider
{
    public:
        /**
         * @brief VisualizationImageProvider constructor.
         */
        explicit VisualizationImageProvider();

        /**
         * @brief Request image from GUI.
         * @param id Id of the image.
         * @param size Size of the image.
         * @param requestedSize Requested size of the image.
         * @return The requested QImage.
         */
        QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

};

#endif // VISUALIZATIONCONTROLLER_H
