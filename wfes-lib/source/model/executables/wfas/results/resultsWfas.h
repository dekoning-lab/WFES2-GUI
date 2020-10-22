#ifndef RESULTSWFAS_H
#define RESULTSWFAS_H


class ResultsWfas {
    public:
        double time;
        dvec probs;
        ResultsWfas();

        ResultsWfas(double time);

        ResultsWfas(dvec probs, double time);

        /**
         * @brief Write results in a CSV file.
         * @param results results to be printed in a CSV file.
         * @param name Name of the file.
         */
        void writeResultsToFile(ResultsWfas *results, std::string name);
};

#endif // RESULTSWFAS_H
