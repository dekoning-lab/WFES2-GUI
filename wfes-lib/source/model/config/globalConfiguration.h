#ifndef GLOBALCONFIGURATION_H
#define GLOBALCONFIGURATION_H

#include <QObject>

#include <wfes-lib_global.h>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT GlobalConfiguration : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool ui_generate_images READ getGenerateImages WRITE setGenerateImages NOTIFY generateImagesChanged)
            Q_PROPERTY(QString ui_save_path READ getSavePath WRITE setSavePath NOTIFY savePathChanged)
            public:
                static bool generateImages;

                static QString savePath;

                GlobalConfiguration() = default;

                bool getGenerateImages();

                void setGenerateImages(bool generate);

                QString getSavePath();

                void setSavePath(QString savePath);

            signals:
                void generateImagesChanged();
                void savePathChanged();
        };
    }
}

#endif // GLOBALCONFIGURATION_H
