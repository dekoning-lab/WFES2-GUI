#include "resultsWfesSwitching.h"

ResultsWfesSwitching::ResultsWfesSwitching() : pExt(std::nan("")), pFix(std::nan("")),
    tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")), tFixStd(std::nan("")),
    rate(std::nan("")), time(std::nan("")), error(""){}

ResultsWfesSwitching::ResultsWfesSwitching(double time) : pExt(std::nan("")), pFix(std::nan("")),
    tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")), tFixStd(std::nan("")),
    rate(std::nan("")), time(time), error(""){}

ResultsWfesSwitching::ResultsWfesSwitching(std::string error) : pExt(std::nan("")), pFix(std::nan("")),
    tExt(std::nan("")), tExtStd(std::nan("")), tFix(std::nan("")), tFixStd(std::nan("")),
    rate(std::nan("")), time(std::nan("")), error(error){}

ResultsWfesSwitching::ResultsWfesSwitching(double tFix, double rate, double time) : pExt(std::nan("")), pFix(std::nan("")),
    tExt(std::nan("")), tExtStd(std::nan("")), tFix(tFix), tFixStd(std::nan("")),
    rate(rate), time(time), error(""){}

ResultsWfesSwitching::ResultsWfesSwitching(double pExt, double pFix, double tExt, double tExtStd, double tFix, double tFixStd, dvec pCondExt, dvec pCondFix, dvec tUncond, dvec tCondExt, dvec tCondFix, double time) :
    pExt(pExt), pFix(pFix),
    tExt(tExt), tExtStd(tExtStd),
    tFix(tFix), tFixStd(tFixStd),
    rate(std::nan("")),
    pCondExt(pCondExt), pCondFix(pCondFix),
    tUncond(tUncond),
    tCondExt(tCondExt), tCondFix(tCondFix),
    time(time), error(""){}

void ResultsWfesSwitching::writeResultsToFile(ResultsWfesSwitching *results, std::string name) {
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
    QFile file(outputPath + QString::fromStdString("Wfes_Single_-_" + s + "_" + name));

    // Open in write mode.
    file.open(QIODevice::WriteOnly);

    QTextStream outStream(&file);

    // Header of the file.
    outStream << "Result, Value" << "\n";

    if(!(boost::math::isnan)(results->pExt))
        outStream << "P_ext, " << results->pExt << "\n";

    if(!(boost::math::isnan)(results->pFix))
        outStream << "P_fix, " << results->pFix << "\n";

    if(!(boost::math::isnan)(results->tExt))
        outStream << "T_ext, " << results->tExt << "\n";

    if(!(boost::math::isnan)(results->tExtStd))
        outStream << "T_ext_std, " << results->tExtStd << "\n";

    if(!(boost::math::isnan)(results->tFix))
        outStream << "T_fix, " << results->tFix << "\n";

    if(!(boost::math::isnan)(results->tFixStd))
        outStream << "T_fix_std, " << results->tFixStd << "\n";

    if(!(boost::math::isnan)(results->rate))
        outStream << "Rate, " << results->rate << "\n";

    if(pCondExt.size() > 0) {
        outStream << "P_cond_ext,";
        for(int i = 0; i < pCondExt.size() - 1; i++){
            outStream << pCondExt[i] << ",";
        }
        outStream << pCondExt[pCondExt.size()-1] << "\n";
    }

    if(pCondFix.size() > 0) {
        outStream << "P_cond_fix,";
        for(int i = 0; i < pCondFix.size() - 1; i++){
            outStream << pCondFix[i] << ",";
        }
        outStream << pCondFix[pCondFix.size()-1] << "\n";
    }

    if(tUncond.size() > 0) {
        outStream << "T_uncond,";
        for(int i = 0; i < tUncond.size() - 1; i++){
            outStream << tUncond[i] << ",";
        }
        outStream << tUncond[tUncond.size()-1] << "\n";
    }

    if(tCondExt.size() > 0) {
        outStream << "T_cond_ext,";
        for(int i = 0; i < tCondExt.size() - 1; i++){
            outStream << tCondExt[i] << ",";
        }
        outStream << tCondExt[tCondExt.size()-1] << "\n";
    }

    if(tCondFix.size() > 0) {
        outStream << "T_cond_fix,";
        for(int i = 0; i < tCondFix.size() - 1; i++){
            outStream << tCondFix[i] << ",";
        }
        outStream << tCondFix[tCondFix.size()-1] << "\n";
    }

    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";

    file.close();

}
