#include "resultsWfafd.h"

ResultsWfafd::ResultsWfafd()
    : time(std::nan("")), error("") {}

ResultsWfafd::ResultsWfafd(double time)
    : time(time), error("") {}

ResultsWfafd::ResultsWfafd(std::string error)
    : time(std::nan("")), error(error) {}

ResultsWfafd::ResultsWfafd(dvec probs, double time)
    : time(time), probs(probs), error("") {}

void ResultsWfafd::writeResultsToFile(ResultsWfafd *results, std::string name) {
    // Let empty. This is not necessary since the prob. dist. are written in a file in the main
    // function of wfafd. Next lines remove the unused parameters warning.
    (void)results;
    (void)name;
}

