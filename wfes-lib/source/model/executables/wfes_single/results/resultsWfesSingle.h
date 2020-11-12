#ifndef RESULTS_H
#define RESULTS_H

#include <source/model/executables/wfes_single/config/configWfesSingle.h>

#include <boost/math/special_functions/fpclassify.hpp>

#include "utils/types.h"

#include <QtGui/QImage>

#include <ctime>

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
    std::string error;

    // Empty constructor
    ResultsWfesSingle();

    // Empty constructor with time
    ResultsWfesSingle(double time);

    // Empty constructor with ERROR
    ResultsWfesSingle(std::string error);

    // Absorption
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double pExt,
            double pFix, double tAbs, double tAbsStd, double tExt,
            double tExtStd, double nExt, double tFix, double tFixStd, double time);

    // Fixation
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double tFix, double tFixStd, double rate, double time);

    // Fundamental
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double time);

    // Equilibrium
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double freqMut, double freqWt, double time);

    // Establishment
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double fEst, double pEst, double tSeg, double tSegStd,
            double tSegExt, double tSegExtStd, double tSegFix,
            double tSegFixStd, double tEst, double tEstStd, double time);

    // Allele Age.
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, double eAlleleAge, double sAlleleAge, bool alelle, double time);

    // Non absorbing.
    ResultsWfesSingle(wfes::config::ModelTypeWfesSingle modelType, bool nonAbsorbing, double time);

    /**
     * @brief Write results in a CSV file.
     * @param results results to be printed in a CSV file.
     * @param name Name of the file.
     */
    void writeResultsToFile(ResultsWfesSingle *results, std::string name);

};

#endif // RESULTS_H
