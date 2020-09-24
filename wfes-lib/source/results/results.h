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
    QImage* imageI;
    QImage* imageQ;
    QImage* imageR;
    QImage* imageN;
    QImage* imageNExt;
    QImage* imageNFix;
    QImage* imageB;
    QImage* imageV;
    QImage* imageE;

    // Empty constructor
    Results();

    // Empty constructor with time
    Results(double time);

    // Absorption
    Results(wfes::config::ModelType modelType, double pExt,
            double pFix, double tAbs, double tAbsStd, double tExt,
            double tExtStd, double nExt, double tFix, double tFixStd, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageNExt, QImage* imageNFix, QImage* imageB);

    // Fixation
    Results(wfes::config::ModelType modelType, double tFix, double tFixStd, double rate, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageB);

    // Fundamental
    Results(wfes::config::ModelType modelType, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageV);

    // Equilibrium
    Results(wfes::config::ModelType modelType, double freqMut, double freqWt, double time,
            QImage* imageI, QImage* imageE);

    // Establishment
    Results(wfes::config::ModelType modelType, double fEst, double pEst, double tSeg, double tSegStd,
            double tSegExt, double tSegExtStd, double tSegFix,
            double tSegFixStd, double tEst, double tEstStd, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR);

    // Allele Age.
    Results(wfes::config::ModelType modelType, double eAlleleAge, double sAlleleAge, bool alelle, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR);

    // Non absorbing.
    Results(wfes::config::ModelType modelType, bool nonAbsorbing, double time,
            QImage* imageI, QImage* imageQ);


};

#endif // RESULTS_H
