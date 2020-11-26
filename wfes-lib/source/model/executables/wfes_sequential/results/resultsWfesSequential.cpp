#include "resultsWfesSequential.h"

using namespace wfes::config;

ResultsWfesSequential::ResultsWfesSequential()
    : pExt(std::nan("")), pFix(std::nan("")), pTmo(std::nan(""))
    , tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan(""))
    , tFixStd(std::nan("")), tTmo(std::nan("")), tTmoStd(std::nan(""))
    , time(std::nan("")), error("") {}

ResultsWfesSequential::ResultsWfesSequential(double time)
    : pExt(std::nan("")), pFix(std::nan("")), pTmo(std::nan("")),
      tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")),
      tFixStd(std::nan("")), tTmo(std::nan("")), tTmoStd(std::nan("")),
      time(time), error("") {}

ResultsWfesSequential::ResultsWfesSequential(std::string error)
    : pExt(std::nan("")), pFix(std::nan("")), pTmo(std::nan("")),
      tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")),
      tFixStd(std::nan("")), tTmo(std::nan("")), tTmoStd(std::nan("")),
      time(std::nan("")), error(error) {}

ResultsWfesSequential::ResultsWfesSequential(double pExt, double pFix, double pTmo, double tExt, double tExtStd, double tFix, double tFixStd, double tTmo, double tTmoStd, double time)
    : pExt(pExt), pFix(pFix), pTmo(pTmo), tExt(tExt), tExtStd(tExtStd),
      tFix(tFix), tFixStd(tFixStd), tTmo(tTmo), tTmoStd(tTmoStd), time(time),
      error("") {}

void ResultsWfesSequential::writeResultsToFile(ResultsWfesSequential *results, std::string name) {
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
    QFile file(outputPath + QString::fromStdString("Wfes_Sequential_-_" + s + "_" + name));

    // Open in write mode.
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    // Header of the file.
    outStream << "Parameter, Value" << "\n";

    outStream << "N, ";
    for(int i = 0; i < ConfigWfesSequential::N.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::N[i]))
            outStream << ConfigWfesSequential::N[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::N[ConfigWfesSequential::N.size()-1]))
        outStream << ConfigWfesSequential::N[ConfigWfesSequential::N.size()-1] << "\n";

    outStream << "t, ";
    for(int i = 0; i < ConfigWfesSequential::t.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::t[i]))
            outStream << ConfigWfesSequential::t[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::t[ConfigWfesSequential::t.size()-1]))
        outStream << ConfigWfesSequential::t[ConfigWfesSequential::t.size()-1] << "\n";

    outStream << "p, ";
    for(int i = 0; i < ConfigWfesSequential::p.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::p[i]))
            outStream << ConfigWfesSequential::p[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::p[ConfigWfesSequential::p.size()-1]))
        outStream << ConfigWfesSequential::p[ConfigWfesSequential::p.size()-1] << "\n";

    outStream << "u, ";
    for(int i = 0; i < ConfigWfesSequential::u.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::u[i]))
            outStream << ConfigWfesSequential::u[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::u[ConfigWfesSequential::u.size()-1]))
        outStream << ConfigWfesSequential::u[ConfigWfesSequential::u.size()-1] << "\n";

    outStream << "v, ";
    for(int i = 0; i < ConfigWfesSequential::v.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::v[i]))
            outStream << ConfigWfesSequential::v[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::v[ConfigWfesSequential::v.size()-1]))
        outStream << ConfigWfesSequential::v[ConfigWfesSequential::v.size()-1] << "\n";

    outStream << "s, ";
    for(int i = 0; i < ConfigWfesSequential::s.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::s[i]))
            outStream << ConfigWfesSequential::s[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::s[ConfigWfesSequential::s.size()-1]))
        outStream << ConfigWfesSequential::s[ConfigWfesSequential::s.size()-1] << "\n";

    outStream << "h, ";
    for(int i = 0; i < ConfigWfesSequential::h.size() - 1; i++) {
        if(!(boost::math::isnan)(ConfigWfesSequential::h[i]))
            outStream << ConfigWfesSequential::h[i] << ", ";
    }
    if(!(boost::math::isnan)(ConfigWfesSequential::h[ConfigWfesSequential::h.size()-1]))
        outStream << ConfigWfesSequential::h[ConfigWfesSequential::h.size()-1] << "\n";

    if(!(boost::math::isnan)(ConfigWfesSequential::a))
        outStream << "a, " << ConfigWfesSequential::a << "\n";

    if(!(boost::math::isnan)(ConfigWfesSequential::c))
        outStream << "c, " << ConfigWfesSequential::c << "\n";


    outStream << "Result, Value" << "\n";

    outStream << "Executable, " << "WFES Sequential" << "\n";

    if(!(boost::math::isnan)(results->pExt))
        outStream << "P_ext, " << results->pExt << "\n";

    if(!(boost::math::isnan)(results->pFix))
        outStream << "P_fix, " << results->pFix << "\n";

    if(!(boost::math::isnan)(results->pTmo))
        outStream << "P_tmo, " << results->pTmo << "\n";

    if(!(boost::math::isnan)(results->tExt))
        outStream << "T_ext, " << results->tExt << "\n";

    if(!(boost::math::isnan)(results->tExtStd))
        outStream << "T_ext_std, " << results->tExtStd << "\n";

    if(!(boost::math::isnan)(results->tFix))
        outStream << "T_fix, " << results->tFix << "\n";

    if(!(boost::math::isnan)(results->tFixStd))
        outStream << "T_fix_std, " << results->tFixStd << "\n";

    if(!(boost::math::isnan)(results->tTmo))
        outStream << "T_tmo, " << results->tTmo << "\n";

    if(!(boost::math::isnan)(results->tFixStd))
        outStream << "T_tmo_std, " << results->tTmoStd << "\n";


    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();

}
