#ifndef RESULTSWFESSWEEP_H
#define RESULTSWFESSWEEP_H

#include "utils/types.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include <ctime>

#include <boost/math/special_functions/fpclassify.hpp>

class ResultsWfesSweep
{
public:
    double tFix;
    double rate;
    double time;

    ResultsWfesSweep();

    ResultsWfesSweep(double t_fix, double rate, double time);

    /**
     * @brief Write results in a CSV file.
     * @param results results to be printed in a CSV file.
     * @param name Name of the file.
     */
    void writeResultsToFile(ResultsWfesSweep *results, std::string name);

};

#endif // RESULTSWFESSWEEP_H
