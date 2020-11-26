#include "resultsWfesSweep.h"

using namespace wfes::config;

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
    outStream << "Parameter, Value" << "\n";

    outStream << "Executable, " << "WFES Sweep" << "\n";

    outStream << "Model type, " << ModelTypeWfesSweepNames[ConfigWfesSweep::ModelTypeWfesSweepToInt(ConfigWfesSweep::modelType)] << "\n";

    if(!(boost::math::isnan)(ConfigWfesSweep::population_size))
        outStream << "N, " << ConfigWfesSweep::population_size << "\n";

    if(!(boost::math::isnan)(ConfigWfesSweep::a))
        outStream << "a, " << ConfigWfesSweep::a << "\n";

    if(!(boost::math::isnan)(ConfigWfesSweep::l))
        outStream << "l, " << ConfigWfesSweep::l << "\n";

    if(!(boost::math::isnan)(ConfigWfesSweep::integration_cutoff))
        outStream << "c, " << ConfigWfesSweep::integration_cutoff << "\n";

    if(!(boost::math::isnan)(ConfigWfesSweep::starting_copies))
        outStream << "p, " << ConfigWfesSweep::starting_copies << "\n";

    outStream << "u, ";
    for(int i = 0; i < ConfigWfesSweep::u.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSweep::u[i]))
            outStream << ConfigWfesSweep::u[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSweep::u[ConfigWfesSweep::u.size()-1]))
        outStream << ConfigWfesSweep::u[ConfigWfesSweep::u.size()-1] << "\n";

    outStream << "v, ";
    for(int i = 0; i < ConfigWfesSweep::v.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSweep::v[i]))
            outStream << ConfigWfesSweep::v[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSweep::v[ConfigWfesSweep::v.size()-1]))
        outStream << ConfigWfesSweep::v[ConfigWfesSweep::v.size()-1] << "\n";

    outStream << "s, ";
    for(int i = 0; i < ConfigWfesSweep::s.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSweep::s[i]))
            outStream << ConfigWfesSweep::s[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSweep::s[ConfigWfesSweep::s.size()-1]))
        outStream << ConfigWfesSweep::s[ConfigWfesSweep::s.size()-1] << "\n";

    outStream << "h, ";
    for(int i = 0; i < ConfigWfesSweep::h.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSweep::h[i]))
            outStream << ConfigWfesSweep::h[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSweep::h[ConfigWfesSweep::h.size()-1]))
        outStream << ConfigWfesSweep::h[ConfigWfesSweep::h.size()-1] << "\n";

    outStream << "Result, Value" << "\n";

    if(!(boost::math::isnan)(results->tFix))
        outStream << "T_fix, " << results->tFix << "\n";

    if(!(boost::math::isnan)(results->rate))
        outStream << "Rate, " << results->rate << "\n";

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();
}
