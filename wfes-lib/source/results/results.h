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
    double time;

    Results();

    Results(double time);

    Results(wfes::config::ModelType modelType, double pExt,
            double pFix, double tAbs, double tAbsStd, double tExt,
            double tExtStd, double nExt, double tFix, double tFixStd, double time);

    Results(wfes::config::ModelType modelType, double freqMut, double freqWt, double time);

    //The boolean is to allow this function to exist and not collide with the previous.
    Results(wfes::config::ModelType modelType, double eAlleleAge, double sAlleleAge, bool allele, double time);

    Results(wfes::config::ModelType modelType, double tFix, double tFixStd, double rate, double time);

    Results(wfes::config::ModelType modelType, double fEst, double pEst, double tSeg, double tSegStd,
            double tSegExt, double tSegExtStd, double tSegFix,
            double tSegFixStd, double tEst, double tEstStd, double time);
};

#endif // RESULTS_H
