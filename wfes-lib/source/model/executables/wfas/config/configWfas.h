#ifndef CONFIGWFAS_H
#define CONFIGWFAS_H

#include <QStandardPaths>
#include <QTextStream>
#include <QString>
#include <QDir>

#include <string>

#include "utils/types.h"

#include <model/config/globalConfiguration.h>

namespace wfes {
    namespace config {

        /**
         * @brief The ConfigWfas class contains the configuration parameters of WFAS as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigWfas {
            public:
                /**
                 * @brief Default constructor for class ConfigWfas.
                 */
                ConfigWfas() = default;

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
                 * @brief Maximum number of generations (G).
                 */
                static lvec G;

                /**
                 * @brief Approximating (down) factor for each population size (f).
                 */
                static dvec f;

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
                 * @brief Initial allele count (p) (i will be ignored).
                 */
                static int p;

                /**
                 * @brief Number of threads for OpenMP (t).
                 */
                static int n_threads;

                /**
                 * @brief Do not project the distribution down.
                 */
                static bool no_proj;

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
                 * @brief Output Dist (Generated distribution).
                 */
                static bool output_Dist;

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
                 * @brief Path output N_Ext (extinction-conditional sojourn).
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
                 * @brief Path output Dist (Generated distribution).
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
                static void saveConfigWfas();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigWfas();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);
            };
    }
}

#endif // CONFIGWFAS_H
