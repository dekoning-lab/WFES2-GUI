#include "resultsWfafle.h"

ResultsWfafle::ResultsWfafle() : time(std::nan("")), error("") {}

ResultsWfafle::ResultsWfafle(double time) : time(time), error("") {}

ResultsWfafle::ResultsWfafle(std::string error) : time(std::nan("")), error(error) {}

ResultsWfafle::ResultsWfafle(dvec probs, double time) : time(time), probs(probs), error("") {}

void ResultsWfafle::writeResultsToFile(ResultsWfafle *results, std::string name)
{
    // Let empty. This is not necessary since the prob. dist. are written in a file in the main
    // function of wfafle.
}

