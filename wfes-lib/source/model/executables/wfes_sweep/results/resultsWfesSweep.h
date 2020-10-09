#ifndef RESULTSWFESSWEEP_H
#define RESULTSWFESSWEEP_H

#include "utils/types.h"


class ResultsWfesSweep
{
public:
    double tFix;
    double rate;
    double time;

    ResultsWfesSweep();

    ResultsWfesSweep(double t_fix, double rate, double time);
};

#endif // RESULTSWFESSWEEP_H
