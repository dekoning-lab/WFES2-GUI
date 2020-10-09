#include "resultsWfesSweep.h"

ResultsWfesSweep::ResultsWfesSweep() :
    tFix(std::nan("")), rate(std::nan("")),time(std::nan("")) {}

ResultsWfesSweep::ResultsWfesSweep(double t_fix, double rate, double time) :
    tFix(t_fix), rate(rate), time(time) {}
