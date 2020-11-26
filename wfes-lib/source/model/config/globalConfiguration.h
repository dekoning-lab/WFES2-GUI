#ifndef GLOBALCONFIGURATION_H
#define GLOBALCONFIGURATION_H

#include <QObject>

#include <wfes-lib_global.h>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT GlobalConfiguration : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool ui_generate_images READ getGenerateImages WRITE setGenerateImages NOTIFY generateImagesChanged)

            public:
                static bool generateImages;

                GlobalConfiguration() = default;

                bool getGenerateImages();

                void setGenerateImages(bool generate);

            signals:

                void generateImagesChanged();
        };
    }
}

#endif // GLOBALCONFIGURATION_H
