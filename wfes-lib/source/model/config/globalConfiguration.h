#ifndef GLOBALCONFIGURATION_H
#define GLOBALCONFIGURATION_H

#include <QDir>
#include <QObject>
#include <QTextStream>
#include <QStandardPaths>

#include <wfes-lib_global.h>

namespace wfes {
    namespace controllers {

        /**
         * @brief The GlobalConfiguration class includes all configuration parameters that applies to the full application.
         */
        class WFESLIBSHARED_EXPORT GlobalConfiguration : public QObject {
            Q_OBJECT
            Q_PROPERTY(bool ui_generate_images READ getGenerateImages WRITE setGenerateImages NOTIFY generateImagesChanged)
            Q_PROPERTY(bool ui_population_scaled READ getPopulationScaled WRITE setPopulationScaled NOTIFY populationScaledChanged)
            Q_PROPERTY(QString ui_save_path READ getSavePath WRITE setSavePath NOTIFY savePathChanged)

            public:
                /**
                 * @brief generateImages If set to true, generate images for "Matrix visualization" Section.
                 */
                static bool generateImages;

                /**
                 * @brief populationScaled If set to true, s, u and v are scaled by population.
                 */
                static bool populationScaled;

                /**
                 * @brief savePath Save path for configuration and download files (not used yet).
                 */
                static QString savePath;

                /**
                  * Default constructor for class globalConfiguration.
                  */
                GlobalConfiguration() = default;

                /**
                 * @brief Send generateImages to GUI.
                 * @return bool containing generateImages.
                 */
                bool getGenerateImages();

                /**
                 * @brief Set generateImages from  GUI.
                 * @param generate value in GUI.
                 */
                void setGenerateImages(bool generate);

                /**
                 * @brief Send populationScaled to GUI.
                 * @return bool containing populationScaled.
                 */
                bool getPopulationScaled();

                /**
                 * @brief Set populationScaled from  GUI.
                 * @param populationScaled value in GUI.
                 */
                void setPopulationScaled(bool populationScaled);

                /**
                 * @brief Send savePath to GUI.
                 * @return QString containing populationScaled.
                 */
                QString getSavePath();

                /**
                 * @brief Set savePath from  GUI.
                 * @param savePath value in GUI.
                 */
                void setSavePath(QString savePath);

                /**
                 * @brief Save configuration into a file.
                 */
                static void saveGlobalConfiguration();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadGlobalConfiguration();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);

            signals:
                /**
                 * @brief Signal for notifying when images has been generated.
                 */
                void generateImagesChanged();
                /**
                 * @brief Signal for notifying when savePath has changed.
                 */
                void savePathChanged();
                /**
                 * @brief Signal for notifying when populationScaled has changed.
                 */
                void populationScaledChanged();
        };
    }
}

#endif // GLOBALCONFIGURATION_H
