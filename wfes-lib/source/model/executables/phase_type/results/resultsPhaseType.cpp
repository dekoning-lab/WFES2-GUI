#include "resultsPhaseType.h"

ResultsPhaseType::ResultsPhaseType()
    : mean(std::nan("")), std(std::nan("")), time(std::nan("")), error("") {}

ResultsPhaseType::ResultsPhaseType(double mean, double std, dvec moments, double time)
    : mean(mean), std(std), time(time), moments(moments), error("") {}

ResultsPhaseType::ResultsPhaseType(double time)
    : mean(std::nan("")), std(std::nan("")), time(time), error("") {}

ResultsPhaseType::ResultsPhaseType(dmat probs, double time)
    : mean(std::nan("")), std(std::nan("")), time(time), probs(probs), error("") {}

ResultsPhaseType::ResultsPhaseType(std::string error)
    : mean(std::nan("")), std(std::nan("")), time(std::nan("")), error(error) {}

void ResultsPhaseType::writeResultsToFile(ResultsPhaseType *results, std::string name) {
    // Get current time for the name of the file.
    time_t t = std::time(0);
    struct tm * now = localtime(&t);
    std::stringstream sstm;
    sstm << (now->tm_hour) << '-' << (now->tm_min) << '-' << now->tm_sec;
    std::string s = sstm.str();

    // Output Path, save in a folder called Wfes inside documents folder.
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/");
    QDir dir;

    // If output path does not exist, create it.
    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    // Create file with generated name.
    QFile file(outputPath + QString::fromStdString("Phase_Type_-_" + s + "_" + name));

    // Open in write mode.
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    // Header of the file.
    outStream << "Result, Value" << "\n";

    if(!(boost::math::isnan)(results->mean))
        outStream << "Mean, " << results->mean << "\n";

    if(!(boost::math::isnan)(results->std))
        outStream << "std, " << results->std << "\n";

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();
}
