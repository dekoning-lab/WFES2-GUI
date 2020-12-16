#include "globalConfiguration.h"

using namespace wfes::controllers;

bool GlobalConfiguration::generateImages = false;
bool GlobalConfiguration::populationScaled = false;
QString GlobalConfiguration::savePath =  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

bool GlobalConfiguration::getGenerateImages() {
    return GlobalConfiguration::generateImages;
}

void GlobalConfiguration::setGenerateImages(bool generate) {
    GlobalConfiguration::generateImages = generate;
    saveGlobalConfiguration();
}

bool GlobalConfiguration::getPopulationScaled() {
    return GlobalConfiguration::populationScaled;
}

void GlobalConfiguration::setPopulationScaled(bool populationScaled) {
    GlobalConfiguration::populationScaled = populationScaled;
    saveGlobalConfiguration();
}

QString GlobalConfiguration::getSavePath() {
    return GlobalConfiguration::savePath;
}

void GlobalConfiguration::setSavePath(QString savePath) {
    GlobalConfiguration::savePath = savePath;
}

void GlobalConfiguration::saveGlobalConfiguration() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/");

    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Global.cfg"));
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    outStream << "Generate Images: " << (GlobalConfiguration::generateImages ? QString("true") : QString("false")) << "\n";
    outStream << "Population-Scaled: " << (GlobalConfiguration::populationScaled ? QString("true") : QString("false")) << "\n";

    file.close();
}

void GlobalConfiguration::loadGlobalConfiguration() {
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/Config/" + "Global.cfg");

    QFile file(outputPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        processLine(line);
    }
}

void GlobalConfiguration::processLine(QString line) {
    QStringList splitted = line.split(": ");
    if(splitted.at(0).compare("Generate Images") == 0) {
        GlobalConfiguration::generateImages = splitted.at(1).compare("true") == 0 ? true : false;
    } else if(splitted.at(0).compare("Population-Scaled") == 0) {
        GlobalConfiguration::populationScaled = splitted.at(1).compare("true") == 0 ? true : false;splitted.at(1).toStdString();
    }
}
