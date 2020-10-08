#ifndef CONFIGWFESSWEEP_H
#define CONFIGWFESSWEEP_H

#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief Enumeration containing possible model types and NONE as special absent type.
         */
        enum class ModelTypeWfesSweep{
            NONE = 0, FIXATION = 1, TIME_DIST_SGV = 2, TIME_DIST_SKIP = 3, TIME_DIST_DUAL = 4
        };

        /**
         * @brief Model Type Names as string, same order as enumeration above to obtain the name of a given enumeration value.
         */
        static const char* ModelTypeWfesSweepNames[] = { "None", "Fixation"};

        class ConfigWfesSweep {
            public:

                /**
                 * @brief Default constructor for class ConfigWfesSweep.
                 */
                ConfigWfesSweep();

                /**
                 * @brief Get integer position of the enumeration value.
                 * @param modelType Modeltype to test position.
                 * @return Position of modelType in enumaration.
                 */
                static int ModelTypeWfesSweepToInt(ModelTypeWfesSweep modelType);

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                /**
                 * @brief Type of model used. (e.g. Fixation).
                 */
                static ModelTypeWfesSweep modelType;

                /**
                 * @brief Size of the population in the Wright Fisher Model (N).
                 */
                static ivec population_sizes;

                /**
                 * @brief Starting number of copies - no integration (p).
                 */
                static ivec starting_copies;

                /**
                 * @brief Backward mutation rates for each component (u).
                 */
                static dvec u;

                /**
                 * @brief Forward mutation rates for each component (u).
                 */
                static dvec v;

                /**
                 * @brief Selection coefficients for each component (s).
                 */
                static dvec s;

                /**
                 * @brief Dominance coefficients for each component (h).
                 */
                static dvec h;

                /**
                 * @brief Tail truncation weight (a).
                 */
                static double a;

                /**
                 * @brief Block Size (b).
                 */
                static int b;

                /**
                 * @brief Number of threads for OpenMP (t).
                 */
                static int n_threads;

                /**
                 * @brief Starting number of copies integration cutoff (c).
                 */
                static double integration_cutoff;

                /**
                 * @brief Transition probability (l).
                 */
                static double l;

                /**
                 * @brief Path to initial probability distribution CSV (I).
                 */
                static std::string initial_distribution_csv;

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
                 * @brief Path output I (Initial probability distribution).
                 */
                static std::string path_output_I;

                /**
                 * @brief Path output Res (Generated results).
                 */
                static std::string path_output_Res;

                /**
                 * @brief Do not perform parameter checks.
                 */
                static bool force;


        };
    }
}
#endif // CONFIGWFESSWEEP_H
