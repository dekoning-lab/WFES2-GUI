#include "resultsWfesSingle.h"

// Empty constructor
ResultsWfesSingle::ResultsWfesSingle() :
    modelType(wfes::config::ModelTypeWfesSingle::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(std::nan("")),

      imageI(nullptr), imageQ(nullptr), imageR(nullptr), imageN(nullptr), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(nullptr), imageE(nullptr){}

// Empty constructor with time
ResultsWfesSingle::ResultsWfesSingle(double time)  :
    modelType(wfes::config::ModelTypeWfesSingle::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time),

      imageI(nullptr), imageQ(nullptr), imageR(nullptr), imageN(nullptr), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(nullptr), imageE(nullptr){}

// Absorption
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double pExt,
                 double pFix, double tAbs, double tAbsStd, double tExt,
                 double tExtStd, double nExt, double tFix, double tFixStd, double time,
                 QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageNExt, QImage* imageNFix, QImage* imageB) :
    modelType(modelType), pExt(pExt), pFix(pFix), tAbs(tAbs), tAbsStd(tAbsStd),
    tExt(tExt), tExtStd(tExtStd), nExt(nExt), tFix(tFix), tFixStd(tFixStd), rate(std::nan("")),

    freqMut(std::nan("")), freqWt(std::nan("")),

    fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
    tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
    tEst(std::nan("")), tEstStd(std::nan("")),

    eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

    time(time),

    imageI(imageI), imageQ(imageQ), imageR(imageR), imageN(imageN), imageNExt(imageNExt), imageNFix(imageNFix), imageB(imageB), imageV(nullptr), imageE(nullptr){}

// Fixation
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double tFix, double tFixStd, double rate, double time, QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageB) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(tFix), tFixStd(tFixStd), rate(rate),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time),

      imageI(imageI), imageQ(imageQ), imageR(imageR), imageN(imageN), imageNExt(nullptr), imageNFix(nullptr), imageB(imageB), imageV(nullptr), imageE(nullptr){}

// Fundamental
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double time, QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageV) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time),

      imageI(imageI), imageQ(imageQ), imageR(imageR), imageN(imageN), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(imageV), imageE(nullptr){}

// Equilibrium
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double freqMut, double freqWt, double time, QImage* imageI, QImage* imageE) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
    tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
    tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

    freqMut(freqMut), freqWt(freqWt),

    fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
    tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
    tEst(std::nan("")), tEstStd(std::nan("")),

    eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

    time(time),

    imageI(imageI), imageQ(nullptr), imageR(nullptr), imageN(nullptr), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(nullptr), imageE(imageE){}

// Establishment
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double fEst, double pEst, double tSeg, double tSegStd, double tSegExt, double tSegExtStd, double tSegFix, double tSegFixStd, double tEst, double tEstStd, double time, QImage* imageI, QImage* imageQ, QImage* imageR) :
      modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(fEst), pEst(pEst), tSeg(tSeg), tSegStd(tSegStd), tSegExt(tSegExt),
      tSegExtStd(tSegExtStd), tSegFix(tSegFix), tSegFixStd(tSegFixStd), tEst(tEst),
      tEstStd(tEstStd),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time),

      imageI(imageI), imageQ(imageQ), imageR(imageR), imageN(nullptr), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(nullptr), imageE(nullptr){}

// Allele Age
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double eAlleleAge, double sAlleleAge, bool allele, double time, QImage* imageI, QImage* imageQ, QImage* imageR) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(eAlleleAge), sAlleleAge(sAlleleAge),

      time(time),

      imageI(imageI), imageQ(imageQ), imageR(imageR), imageN(nullptr), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(nullptr), imageE(nullptr){}

// Non absorbing
ResultsWfesSingle::ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, bool nonAbsorbing, double time, QImage* imageI, QImage* imageQ) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time),

      imageI(imageI), imageQ(imageQ), imageR(nullptr), imageN(nullptr), imageNExt(nullptr), imageNFix(nullptr), imageB(nullptr), imageV(nullptr), imageE(nullptr){}



void ResultsWfesSingle::writeResultsToFile(ResultsWfesSingle *results, std::string name)
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

    QFile file(outputPath + QString::fromStdString("Wfes_Single_-_" + s + "_" + name));
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

    if(!(boost::math::isnan)(results->tAbs))
        outStream << "T_abs, " << results->tAbs << "\n";

    if(!(boost::math::isnan)(results->tAbsStd))
        outStream << "T_abs_std, " << results->tAbsStd << "\n";

    if(!(boost::math::isnan)(results->tExt))
        outStream << "T_ext, " << results->tExt << "\n";

    if(!(boost::math::isnan)(results->tExtStd))
        outStream << "T_ext_std, " << results->tExtStd << "\n";

    if(!(boost::math::isnan)(results->nExt))
        outStream << "N_ext, " << results->nExt << "\n";

    if(!(boost::math::isnan)(results->tFix))
        outStream << "T_fix, " << results->tFix << "\n";

    if(!(boost::math::isnan)(results->tFixStd))
        outStream << "T_fix_std, " << results->tFixStd << "\n";

    if(!(boost::math::isnan)(results->rate))
        outStream << "Rate, " << results->rate << "\n";

    if(!(boost::math::isnan)(results->freqMut))
        outStream << "E[freq mut], " << results->freqMut << "\n";

    if(!(boost::math::isnan)(results->freqWt))
        outStream << "E[freq  wt], " << results->freqWt << "\n";

    if(!(boost::math::isnan)(results->fEst))
        outStream << "F_est, " << results->fEst << "\n";

    if(!(boost::math::isnan)(results->pEst))
        outStream << "P_est, " << results->fEst << "\n";

    if(!(boost::math::isnan)(results->tSeg))
        outStream << "T_seg, " << results->tSeg << "\n";

    if(!(boost::math::isnan)(results->tSegStd))
        outStream << "T_seg_std, " << results->tSegStd << "\n";

    if(!(boost::math::isnan)(results->tSegExt))
        outStream << "T_seg_ext, " << results->tSegExt << "\n";

    if(!(boost::math::isnan)(results->tSegExtStd))
        outStream << "T_seg_ext_std, " << results->tSegExtStd << "\n";

    if(!(boost::math::isnan)(results->tSegFix))
        outStream << "T_seg_fix, " << results->tSegFix << "\n";

    if(!(boost::math::isnan)(results->tSegFixStd))
        outStream << "T_seg_fix_std, " << results->tSegFixStd << "\n";

    if(!(boost::math::isnan)(results->tEst))
        outStream << "T_est, " << results->tEst << "\n";

    if(!(boost::math::isnan)(results->tEstStd))
        outStream << "T_est_std, " << results->tEstStd << "\n";

    if(!(boost::math::isnan)(results->eAlleleAge))
        outStream << "E(A), " << results->eAlleleAge << "\n";

    if(!(boost::math::isnan)(results->sAlleleAge))
        outStream << "S(A), " << results->sAlleleAge << "\n";


    if(!(boost::math::isnan)(results->time))
        outStream << "Time, " << results->time << "\n";


    file.close();
}

