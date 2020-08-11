#include "results.h"

Results::Results() :
    modelType(wfes::config::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(std::nan(""))
{

}

Results::Results(double time)  :
    modelType(wfes::config::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time)
{

}

Results::Results(wfes::config::ModelType modelType, double pExt, double pFix, double tAbs, double tAbsStd, double tExt, double tExtStd, double nExt, double tFix, double tFixStd, double time) :
    modelType(modelType), pExt(pExt), pFix(pFix), tAbs(tAbs), tAbsStd(tAbsStd),
    tExt(tExt), tExtStd(tExtStd), nExt(nExt), tFix(tFix), tFixStd(tFixStd), rate(std::nan("")),

    freqMut(std::nan("")), freqWt(std::nan("")),

    fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
    tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
    tEst(std::nan("")), tEstStd(std::nan("")),

    eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

    time(time)
{

}

Results::Results(wfes::config::ModelType modelType, double freqMut, double freqWt, double time) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
    tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
    tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

    freqMut(freqMut), freqWt(freqWt),

    fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
    tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
    tEst(std::nan("")), tEstStd(std::nan("")),

    eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

    time(time)
{

}

Results::Results(wfes::config::ModelType modelType, double eAlleleAge, double sAlleleAge, bool allele, double time) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(eAlleleAge), sAlleleAge(sAlleleAge),

      time(time)
{

}

Results::Results(wfes::config::ModelType modelType, double tFix, double tFixStd, double rate, double time) :
    modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(tFix), tFixStd(tFixStd), rate(rate),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(std::nan("")), pEst(std::nan("")), tSeg(std::nan("")), tSegStd(std::nan("")),
      tSegExt(std::nan("")), tSegExtStd(std::nan("")), tSegFix(std::nan("")), tSegFixStd(std::nan("")),
      tEst(std::nan("")), tEstStd(std::nan("")),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time)
{

}

Results::Results(wfes::config::ModelType modelType, double fEst, double pEst, double tSeg, double tSegStd, double tSegExt, double tSegExtStd, double tSegFix, double tSegFixStd, double tEst, double tEstStd, double time) :
      modelType(modelType), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")),
      tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")),
      tFix(std::nan("")), tFixStd(std::nan("")), rate(std::nan("")),

      freqMut(std::nan("")), freqWt(std::nan("")),

      fEst(fEst), pEst(pEst), tSeg(tSeg), tSegStd(tSegStd), tSegExt(tSegExt),
      tSegExtStd(tSegExtStd), tSegFix(tSegFix), tSegFixStd(tSegFixStd), tEst(tEst),
      tEstStd(tEstStd),

      eAlleleAge(std::nan("")), sAlleleAge(std::nan("")),

      time(time)

{

}

