#ifndef RESULTS_H
#define RESULTS_H

#include <source/model/executables/wfes_single/config/configWfesSingle.h>

#include <boost/math/special_functions/fpclassify.hpp>

#include "utils/types.h"

#include <QtGui/QImage>

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

class ResultsWfesSingle
{
public:
    wfes::config::ModelTypeWfesSingle modelType;
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
    ResultsWfesSingle();

    // Empty constructor with time
    ResultsWfesSingle(double time);

    // Absorption
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double pExt,
            double pFix, double tAbs, double tAbsStd, double tExt,
            double tExtStd, double nExt, double tFix, double tFixStd, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageNExt, QImage* imageNFix, QImage* imageB);

    // Fixation
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double tFix, double tFixStd, double rate, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageB);

    // Fundamental
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR, QImage* imageN, QImage* imageV);

    // Equilibrium
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double freqMut, double freqWt, double time,
            QImage* imageI, QImage* imageE);

    // Establishment
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double fEst, double pEst, double tSeg, double tSegStd,
            double tSegExt, double tSegExtStd, double tSegFix,
            double tSegFixStd, double tEst, double tEstStd, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR);

    // Allele Age.
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double eAlleleAge, double sAlleleAge, bool alelle, double time,
            QImage* imageI, QImage* imageQ, QImage* imageR);

    // Non absorbing.
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, bool nonAbsorbing, double time,
            QImage* imageI, QImage* imageQ);

    /**
     * @brief Write results in a CSV file.
     * @param results results to be printed in a CSV file.
     * @param name Name of the file.
     */
    void writeResultsToFile(ResultsWfesSingle *results, std::string name);

};

#endif // RESULTS_H
