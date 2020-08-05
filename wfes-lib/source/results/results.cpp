#include "results.h"

Results::Results()
    : modelType(wfes::config::NONE), pExt(std::nan("")), pFix(std::nan("")), tAbs(std::nan("")), tAbsStd(std::nan("")), tExt(std::nan("")), tExtStd(std::nan("")), nExt(std::nan("")), tFix(std::nan("")), tFixStd(std::nan(""))
{

}

Results::Results(wfes::config::ModelType modelType, double pExt, double pFix, double tAbs, double tAbsStd, double tExt, double tExtStd, double nExt, double tFix, double tFixStd)
    : modelType(modelType), pExt(pExt), pFix(pFix), tAbs(tAbs), tAbsStd(tAbsStd), tExt(tExt), tExtStd(tExtStd), nExt(nExt), tFix(tFix), tFixStd(tFixStd)
{}
