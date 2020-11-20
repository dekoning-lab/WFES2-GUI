#include "resultsWfesSweep.h"

ResultsWfesSweep::ResultsWfesSweep() :
    tFix(std::nan("")), rate(std::nan("")),time(std::nan("")),
    error("") {}

ResultsWfesSweep::ResultsWfesSweep(double time) :
    tFix(std::nan("")), rate(std::nan("")),time(time),
    error("") {}

ResultsWfesSweep::ResultsWfesSweep(std::string error) :
    tFix(std::nan("")), rate(std::nan("")),time(std::nan("")),
    error(error) {}

ResultsWfesSweep::ResultsWfesSweep(double t_fix, double rate, double time) :
    tFix(t_fix), rate(rate), time(time),
    error("") {}

void ResultsWfesSweep::writeResultsToFile(ResultsWfesSweep *results, std::string name) {
    // Get current time for the name of the file.
    time_t t = std::time(0);
    struct tm * now = localtime(&t);
    std::stringstream sstm;
    sstm << (now->tm_hour) << '-' << (now->tm_min) << '-' << now->tm_sec;
    std::string s = sstm.str();

    // Output Path, save in a folder called Wfes inside documents folder.
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/");


    // If output path does not exist, create it.
    QDir dir;
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    // Create file with generated name.
    QFile file(outputPath + QString::fromStdString("Wfes_Sweep_-_" + s + "_" + name));

    // Open in write mode.
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    // Header of the file.
    outStream << "Result, Value" << "\n";

    if(!(boost::math::isnan)(results->tFix))
        outStream << "T_fix, " << results->tFix << "\n";

    if(!(boost::math::isnan)(results->rate))
        outStream << "Rate, " << results->rate << "\n";

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();
}
