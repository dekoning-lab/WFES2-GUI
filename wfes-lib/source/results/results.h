#ifndef RESULTS_H
#define RESULTS_H

#include <config/config.h>

#include <QtGui/QImage>


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
    QImage* initialDistribution;
    QImage* imageQ;
    QImage* imageR;
    QImage* imageN;
    QImage* imageNExt;
    QImage* imageNFix;
    QImage* imageV;
    QImage* imageE;

    // Empty constructor
    Results();

    // Empty constructor with time
    Results(double time);

    // Absorption
    Results(wfes::config::ModelType modelType, double pExt,
            double pFix, double tAbs, double tAbsStd, double tExt,
            double tExtStd, double nExt, double tFix, double tFixStd, double time);

    // Fixation
    Results(wfes::config::ModelType modelType, double tFix, double tFixStd, double rate, double time);

    // Fundamental
    Results(wfes::config::ModelType modelType, double time);

    // Equilibrium
    Results(wfes::config::ModelType modelType, double freqMut, double freqWt, double time);

    // Establishment
    Results(wfes::config::ModelType modelType, double fEst, double pEst, double tSeg, double tSegStd,
            double tSegExt, double tSegExtStd, double tSegFix,
            double tSegFixStd, double tEst, double tEstStd, double time);

    // Allele Age.
    Results(wfes::config::ModelType modelType, double eAlleleAge, double sAlleleAge, bool alelle, double time);

    // Non absorbing.
    Results(wfes::config::ModelType modelType, bool nonAbsorbing, double time);


};

#endif // RESULTS_H
