#include "resultsWfesSweep.h"

ResultsWfesSweep::ResultsWfesSweep() :
    tFix(std::nan("")), rate(std::nan("")),time(std::nan("")) {}

ResultsWfesSweep::ResultsWfesSweep(double t_fix, double rate, double time) :
    tFix(t_fix), rate(rate), time(time) {}

void ResultsWfesSweep::writeResultsToFile(ResultsWfesSweep *results, std::string name) {

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

    if(!(boost::math::isnan)(results->tFix))
        outStream << "T_fix, " << results->tFix << "\n";

    if(!(boost::math::isnan)(results->rate))
        outStream << "Rate, " << results->rate << "\n";

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();
}
