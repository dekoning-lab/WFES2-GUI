#include "resultsWfas.h"

ResultsWfas::ResultsWfas()
    : time(std::nan("")), error("") {}

ResultsWfas::ResultsWfas(double time)
    : time(time), error("") {}

ResultsWfas::ResultsWfas(std::string error)
    : time(std::nan("")), error(error) {}

ResultsWfas::ResultsWfas(dvec probs, double time)
    : time(time), probs(probs), error("") {}

void ResultsWfas::writeResultsToFile(ResultsWfas *results, std::string name) {
    // Let empty. This is not necessary since the prob. dist. are written in a file in the main
    // function of wfafle. Next lines remove the unused parameters warning.
    (void)results;
    (void)name;
}

