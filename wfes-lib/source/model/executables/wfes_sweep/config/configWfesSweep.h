#ifndef CONFIGWFESSWEEP_H
#define CONFIGWFESSWEEP_H

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
         * @brief Enumeration containing possible model types and NONE as special absent type.
         */
        enum class ModelTypeWfesSweep{
            NONE = 0, FIXATION = 1
        };

        /**
         * @brief Model Type Names as string, same order as enumeration above to obtain the name of a given enumeration value.
         */
        static const char* ModelTypeWfesSweepNames[] = { "None", "Fixation"};

        /**
         * @brief The ConfigWfesSweep class contains the configuration parameters of Wfes Sweep as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigWfesSweep {
            public:

                /**
                 * @brief Default constructor for class ConfigWfesSweep.
                 */
                ConfigWfesSweep() = default;

                /**
                 * @brief Get an integer representing a model type (Position in the enum).
                 * @param modelType Model Type that we want to extract the numer (position).
                 * @return Position of the Model Type in the enum.
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
                static int population_size;

                /**
                 * @brief Starting number of copies - no integration (p).
                 */
                static int starting_copies;

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
                 * @brief Output I (Initial probability distribution).
                 */
                static bool output_I;

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

                /**
                 * @brief Save configuration into a file.
                 */
                static void saveConfigWfesSweep();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigWfesSweep();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);
        };
    }
}
#endif // CONFIGWFESSWEEP_H
