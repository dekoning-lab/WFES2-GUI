#include "resultsPhaseType.h"

ResultsPhaseType::ResultsPhaseType() :
    mean(std::nan("")), std(std::nan("")),time(std::nan("")) {}

ResultsPhaseType::ResultsPhaseType(double mean, double std, double time) :
    mean(mean), std(std), time(time) {}

ResultsPhaseType::ResultsPhaseType(double time) :
    mean(std::nan("")), std(std::nan("")), time(time) {}

void ResultsPhaseType::writeResultsToFile(ResultsPhaseType *results, std::string name)
{

    time_t t = std::time(0);   // get time now
    struct tm * now = localtime(&t);
    std::stringstream sstm;
    sstm << (now->tm_hour) << '-' << (now->tm_min) << '-' << now->tm_sec;
    std::string s = sstm.str();

    //TODO put outputPath in global configuration.
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    QFile file(outputPath + QString::fromStdString("Wfes_Sweep_-_" + s + "_" + name));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Result, Value" << "\n";

    if(!(boost::math::isnan)(results->mean))
        outStream << "Mean, " << results->mean << "\n";

    if(!(boost::math::isnan)(results->std))
        outStream << "std, " << results->std << "\n";

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();
}
