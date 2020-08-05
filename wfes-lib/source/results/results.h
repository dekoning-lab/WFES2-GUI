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

    Results();
    Results(wfes::config::ModelType modelType, double pExt, double pFix, double tAbs, double tAbsStd, double tExt, double tExtStd, double nExt, double tFix, double tFixStd);
};

#endif // RESULTS_H
