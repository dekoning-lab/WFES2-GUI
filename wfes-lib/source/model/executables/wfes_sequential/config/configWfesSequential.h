#ifndef CONFIGWFESSEQUENTIAL_H
#define CONFIGWFESSEQUENTIAL_H

#include <QStandardPaths>
#include <QTextStream>
#include <QString>
#include <QDir>

#include <string>

#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief The ConfigWfesSequential class contains the configuration parameters of Wfes Sequential as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigWfesSequential {
            public:
                /**
                 * @brief Default constructor for class ConfigWfesSequential.
                 */
                ConfigWfesSequential() = default;

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                /**
                 * @brief Size of the population for each component (N).
                 */
                static lvec N;

                /**
                 * @brief Expected time spent in each model t)
                 */
                static dvec t;

                /**
                 * @brief Starting probabilities (p).
                 */
                static dvec p;

                /**
                 * @brief Selection coefficients for each component (s).
                 */
                static dvec s;

                /**
                 * @brief Dominance coefficients for each component (h).
                 */
                static dvec h;

                /**
                 * @brief Backward mutation rates for each component (u).
                 */
                static dvec u;

                /**
                 * @brief Forward mutation rates for each component (u).
                 */
                static dvec v;

                /**
                 * @brief Tail truncation weight (a).
                 */
                static double a;

                /**
                 * @brief Integration Cutoff (c).
                 */
                static double c;

                /**
                 * @brief Number of threads for OpenMP (t).
                 */
                static int n_threads;

                /**
                 * @brief Path to initial probability distribution CSV (I).
                 */
                static std::string initial_distribution_csv;

                /**
                 * @brief Output Q.
                 */
                static bool output_Q;

                /**
                 * @brief Output R.
                 */
                static bool output_R;

                /**
                 * @brief Output N.
                 */
                static bool output_N;

                /**
                 * @brief Output B.
                 */
                static bool output_B;

                /**
                 * @brief Output I.
                 */
                static bool output_I;

                /**
                 * @brief Path output N_Ext (extintion-conditional sojourn).
                 */
                static bool output_N_Ext;

                /**
                 * @brief Path output N_fix (fixation-conditional sojourn).
                 */
                static bool output_N_Fix;

                /**
                 * @brief Path output N_tmo (timeout-conditional sojourn).
                 */
                static bool output_N_Tmo;

                /**
                 * @brief Output Res (Generated results).
                 */
                static bool output_Res;

                /**
                 * @brief Path output Q.
                 */
                static std::string path_output_Q;

                /**
                 * @brief Path output R.
                 */
                static std::string path_output_R;

                /**
                 * @brief Path output N.
                 */
                static std::string path_output_N;

                /**
                 * @brief Path output B.
                 */
                static std::string path_output_B;

                /**
                 * @brief Path output I.
                 */
                static std::string path_output_I;

                /**
                 * @brief Path output N_ext (extintion-conditional sojourn).
                 */
                static std::string path_output_N_Ext;

                /**
                 * @brief Path output N_fix (fixation-conditional sojourn).
                 */
                static std::string path_output_N_Fix;

                /**
                 * @brief Path output N_tmo (timeout-conditional sojourn).
                 */
                static std::string path_output_N_Tmo;

                /**
                 * @brief Path output Res (Generated results).
                 */
                static std::string path_output_Res;

                /**
                 * @brief Do not perform parameter checks.
                 */
                static bool force;

                /**
                 * @brief Number of components used.
                 */
                static int num_comp;

                /**
                 * @brief Save configuration into a file.
                 */
                static void saveConfigWfesSequential();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigWfesSequential();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);

        };
    }
}

#endif // CONFIGWFESSEQUENTIAL_H
