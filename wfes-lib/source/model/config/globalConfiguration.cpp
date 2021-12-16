#include "globalConfiguration.h"

using namespace wfes::controllers;

bool GlobalConfiguration::generateImages = false;
bool GlobalConfiguration::populationScaled = false;
QString GlobalConfiguration::savePath =  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
long long GlobalConfiguration::systemMemory = 0;

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

void GlobalConfiguration::estimateRAM() {
    #if defined(Q_OS_LINUX)
        long pages = sysconf(_SC_PHYS_PAGES);
        long page_size = sysconf(_SC_PAGE_SIZE);
        systemMemory = pages * page_size;
    #elif defined(Q_OS_MAC)
        long pages = sysconf(_SC_PHYS_PAGES);
        long page_size = sysconf(_SC_PAGE_SIZE);
        systemMemory = pages * page_size;
    #elif defined(Q_OS_WIN)
        MEMORYSTATUSEX status;
        status.dwLength = sizeof(status);
        GlobalMemoryStatusEx(&status);
        systemMemory = status.ullTotalPhys;
    #endif
}

void GlobalConfiguration::createConfigFilePardisoOOC() {
    QString outputPath(".");

    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("pardiso_ooc.cfg"));
    qDebug() << file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    QString pathPardisoOOC(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/temp/");
    if (!dir.exists(pathPardisoOOC))
        dir.mkpath(pathPardisoOOC);

    outStream << "MKL_PARDISO_OOC_PATH = " << pathPardisoOOC << "\n";

    // We only reserve 70% of full memory for OOC.
    outStream << "MKL_PARDISO_OOC_MAX_CORE_SIZE = " << QString::fromStdString(std::to_string((int)(systemMemory*0.0000007))) << "\n";
    outStream << "MKL_PARDISO_OOC_MAX_SWAP_SIZE = " << QString::fromStdString("0") << "\n";
    outStream << "MKL_PARDISO_OOC_KEEP_FILE = " << QString::fromStdString("0") << "\n";

    file.close();
}
