#ifndef RESULTS_H
#define RESULTS_H

#import <config/config.h>


class Results
{
public:
    wfes::config::ModelType modelType;
    double pExt;
    double pFix;
    double tAbs;
    double tAbsStd;
    double tExt;
    double tExtStd;
    double nExt;
    double tFix;
    double tFixStd;
    double rate;
    double freqMut;
    double freqWt;
    double fEst;
    double pEst;
    double tSeg;
    double tSegStd;
    double tSegExt;
    double tSegExtStd;
    double tSegFix;
    double tSegFixStd;
    double tEst;
    double tEstStd;
    double eAlleleAge;
    double sAlleleAge;

    Results();

    Results(wfes::config::ModelType modelType, double pExt,
            double pFix, double tAbs, double tAbsStd, double tExt,
            double tExtStd, double nExt, double tFix, double tFixStd);

    Results(wfes::config::ModelType modelType, double freqMut, double freqWt);

    //The boolean is to allow this function to exist and not collide with the previous.
    Results(wfes::config::ModelType modelType, double eAlleleAge, double sAlleleAge, bool allele);

    Results(wfes::config::ModelType modelType, double tFix, double tFixStd, double rate);

    Results(wfes::config::ModelType modelType, double fEst, double pEst, double tSeg, double tSegStd,
            double tSegExt, double tSegExtStd, double tSegFix,
            double tSegFixStd, double tEst, double tEstStd);
};

#endif // RESULTS_H
