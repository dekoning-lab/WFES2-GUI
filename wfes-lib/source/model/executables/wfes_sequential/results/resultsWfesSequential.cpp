#include "resultsWfesSequential.h"

ResultsWfesSequential::ResultsWfesSequential() : pExt(std::nan("")), pFix(std::nan("")), pTmo(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")), tFixStd(std::nan("")), tTmo(std::nan("")), tTmoStd(std::nan("")), time(std::nan("")) {}

ResultsWfesSequential::ResultsWfesSequential(double time) : pExt(std::nan("")), pFix(std::nan("")), pTmo(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")), tFixStd(std::nan("")), tTmo(std::nan("")), tTmoStd(std::nan("")), time(time) {}

ResultsWfesSequential::ResultsWfesSequential(double pExt, double pFix, double pTmo, double tExt, double tExtStd, double tFix, double tFixStd, double tTmo, double tTmoStd, double time) : pExt(pExt), pFix(pFix), pTmo(pTmo), tExt(tExt), tExtStd(tExtStd), tFix(tFix), tFixStd(tFixStd), tTmo(tTmo), tTmoStd(tTmoStd), time(time) {}

void ResultsWfesSequential::writeResultsToFile(ResultsWfesSequential *results, std::string name)
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

    QFile file(outputPath + QString::fromStdString("Wfes_Sequential_-_" + s + "_" + name));
    file.open(QIODevice::WriteOnly);

    if(!file.isOpen()) {
        qDebug() << "The file is not open.";
    }

    QTextStream outStream(&file);

    outStream << "Result, Value" << "\n";

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
