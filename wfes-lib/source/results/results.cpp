#include "results.h"

// Empty constructor
Results::Results() :
    modelType(wfes::config::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
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
Results::Results(double time)  :
    modelType(wfes::config::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
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
Results::Results(wfes::config::ModelType modelType, double pExt,
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
Results::Results(wfes::config::ModelType modelType, double tFix, double tFixStd, double rate, double time, QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageB) :
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
Results::Results(wfes::config::ModelType modelType, double time, QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageV) :
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
Results::Results(wfes::config::ModelType modelType, double freqMut, double freqWt, double time, QImage* imageI, QImage* imageE) :
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
Results::Results(wfes::config::ModelType modelType, double fEst, double pEst, double tSeg, double tSegStd, double tSegExt, double tSegExtStd, double tSegFix, double tSegFixStd, double tEst, double tEstStd, double time, QImage* imageI, QImage* imageQ, QImage* imageR) :
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
Results::Results(wfes::config::ModelType modelType, double eAlleleAge, double sAlleleAge, bool allele, double time, QImage* imageI, QImage* imageQ, QImage* imageR) :
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
Results::Results(wfes::config::ModelType modelType, bool nonAbsorbing, double time, QImage* imageI, QImage* imageQ) :
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


