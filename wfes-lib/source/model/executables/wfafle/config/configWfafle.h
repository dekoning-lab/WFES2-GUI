#ifndef CONFIGWFAFLE_H
#define CONFIGWFAFLE_H

#include "utils/types.h"

namespace wfes {
    namespace config {

        class ConfigWfafle {
            public:
                /**
                 * @brief Default constructor for class ConfigWfafle.
                 */
                ConfigWfafle();

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                static ivec N;

                static ivec G;

                static dvec s;

                static dvec h;

                static dvec u;

                static dvec v;

                static double a;

                static int p;

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
                 * @brief Verbose solver output (TODO Not Used In GUI.)
                 */
                static bool verbose;

                /**
                 * @brief Error messages to show if there is an error.
                 */
                static std::string error;

                /**
                 * @brief Number of components used.
                 */
                static int num_comp;

        };
    }
}
#endif // CONFIGWFAFLE_H

