#include "resultsWfafle.h"

ResultsWfafle::ResultsWfafle() : time(std::nan("")){}

ResultsWfafle::ResultsWfafle(double time) : time(time) {}

ResultsWfafle::ResultsWfafle(dvec probs, double time) : time(time), probs(probs){}

void ResultsWfafle::writeResultsToFile(ResultsWfafle *results, std::string name)
{
    // Let empty. This is not necessary since the prob. dist. are written in a file in the main
    // function of wfafle.
}

