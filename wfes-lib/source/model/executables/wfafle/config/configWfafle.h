#ifndef CONFIGWFAFLE_H
#define CONFIGWFAFLE_H

#include <QStandardPaths>
#include <QTextStream>
#include <QString>
#include <QDir>

#include <string>

#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief The ConfigWfafle class contains the configuration parameters of WFAFLE as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigWfafle {
            public:
                /**
                 * @brief Default constructor for class ConfigWfafle.
                 */
                ConfigWfafle() = default;

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
                static ivec N;

                /**
                 * @brief Maximum number of generations (G).
                 */
                static ivec G;

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
                 * @brief Initial allele count (p).
                 */
                static int p;

                /**
                 * @brief Number of threads for OpenMP (t).
                 */
                static int n_threads;

                /**
                 * @brief Path to initial probability distribution CSV (I).
                 */
                static std::string initial_distribution_csv;

                /**
                 * @brief Output I (Initial probability distribution).
                 */
                static bool output_I;

                /**
                 * @brief Output Res (Generated results).
                 */
                static bool output_Dist;

                /**
                 * @brief Path output I (Initial probability distribution).
                 */
                static std::string path_output_I;

                /**
                 * @brief Path output Dist (Generated results).
                 */
                static std::string path_output_Dist;

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
                static void saveConfigWfafle();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigWfafle();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);
        };
    }
}
#endif // CONFIGWFAFLE_H

