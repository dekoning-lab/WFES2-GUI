#ifndef RESULTSWFESSWITCHING_H
#define RESULTSWFESSWITCHING_H

#include <source/model/executables/wfes_sequential/config/configWfesSequential.h>

#include <boost/math/special_functions/fpclassify.hpp>

#include "utils/types.h"

#include <QtGui/QImage>

#include <ctime>

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

class ResultsWfesSwitching {
public:
    double pExt;
    double pFix;
    double tExt;
    double tExtStd;
    double tFix;
    double tFixStd;
    double rate;
    dvec pCondExt;
    dvec pCondFix;
    dvec tUncond;
    dvec tCondExt;
    dvec tCondFix;
    double time;


    ResultsWfesSwitching();

    ResultsWfesSwitching(double time);

    // Fixation
    ResultsWfesSwitching(double tFix, double rate, double time);

    // Absorption
    ResultsWfesSwitching(double pExt, double pFix, double tExt, double tExtStd, double tFix, double tFixStd, dvec pCondExt, dvec pCondFix, dvec tUncond, dvec tCondExt, dvec tCondFix, double time);

    /**
     * @brief Write results in a CSV file.
     * @param results results to be printed in a CSV file.
     * @param name Name of the file.
     */
    void writeResultsToFile(ResultsWfesSwitching *results, std::string name);

};

#endif // RESULTSWFESSWITCHING_H
