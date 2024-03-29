#include "resultsPhaseType.h"

using namespace wfes::config;

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
    outStream << "Parameter, Value" << "\n";

    outStream << "Executable, " << "Phase Type" << "\n";

    outStream << "Model type, " << ModelTypePhaseTypeNames[ConfigPhaseType::ModelTypePhaseTypeToInt(ConfigPhaseType::modelType)] << "\n";

    if(!(boost::math::isnan)(ConfigPhaseType::population_size))
        outStream << "N, " << ConfigPhaseType::population_size << "\n";

    if(!(boost::math::isnan)(ConfigPhaseType::a))
        outStream << "a, " << ConfigPhaseType::a << "\n";

    if(!(boost::math::isnan)(ConfigPhaseType::s))
        outStream << "s, " << ConfigPhaseType::s << "\n";

    if(!(boost::math::isnan)(ConfigPhaseType::h))
        outStream << "h, " << ConfigPhaseType::h << "\n";

    if(!(boost::math::isnan)(ConfigPhaseType::u))
        outStream << "u, " << ConfigPhaseType::u << "\n";

    if(!(boost::math::isnan)(ConfigPhaseType::v))
        outStream << "v, " << ConfigPhaseType::v << "\n";

    if(ConfigPhaseType::modelType == ModelTypePhaseType::PHASE_TYPE_DIST) {
        if(!(boost::math::isnan)(ConfigPhaseType::integration_cutoff))
            outStream << "c, " << ConfigPhaseType::integration_cutoff << "\n";

        if(!(boost::math::isnan)(ConfigPhaseType::max_t))
            outStream << "m, " << ConfigPhaseType::max_t << "\n";

        outStream << "r, " << (ConfigPhaseType::no_rem ? "true" : "false") << "\n";
    } else if (ConfigPhaseType::modelType == ModelTypePhaseType::PHASE_TYPE_MOMENTS) {
        if(!(boost::math::isnan)(ConfigPhaseType::k))
            outStream << "k, " << ConfigPhaseType::k << "\n";
    }

    outStream << "Result, Value" << "\n";

    if(!(boost::math::isnan)(results->mean))
        outStream << "Mean, " << results->mean << "\n";

    if(!(boost::math::isnan)(results->std))
        outStream << "std, " << results->std << "\n";

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();
}
