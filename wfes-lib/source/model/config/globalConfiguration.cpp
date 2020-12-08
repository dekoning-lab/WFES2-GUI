#include "globalConfiguration.h"

#include <QStandardPaths>

using namespace wfes::controllers;

bool GlobalConfiguration::generateImages = false;
bool GlobalConfiguration::populationScaled = false;
QString GlobalConfiguration::savePath =  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

bool GlobalConfiguration::getGenerateImages() {
    return GlobalConfiguration::generateImages;
}

void GlobalConfiguration::setGenerateImages(bool generate) {
    GlobalConfiguration::generateImages = generate;
}

bool GlobalConfiguration::getPopulationScaled() {
    return GlobalConfiguration::populationScaled;
}

void GlobalConfiguration::setPopulationScaled(bool populationScaled) {
    GlobalConfiguration::populationScaled = populationScaled;
}

QString GlobalConfiguration::getSavePath() {
    return GlobalConfiguration::savePath;
}

void GlobalConfiguration::setSavePath(QString savePath) {
    GlobalConfiguration::savePath = savePath;
}
