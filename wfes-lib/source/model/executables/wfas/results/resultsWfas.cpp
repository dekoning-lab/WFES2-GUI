#include "resultsWfas.h"

ResultsWfas::ResultsWfas() : time(std::nan("")){}

ResultsWfas::ResultsWfas(double time) : time(time) {}

ResultsWfas::ResultsWfas(dvec probs, double time) : time(time), probs(probs){}

void ResultsWfas::writeResultsToFile(ResultsWfas *results, std::string name)
{
    // Let empty. This is not necessary since the prob. dist. are written in a file in the main
    // function of wfafle.
}

