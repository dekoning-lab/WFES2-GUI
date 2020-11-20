#ifndef CONFIGTIMEDIST_H
#define CONFIGTIMEDIST_H

#include <QStandardPaths>
#include <QTextStream>
#include <QString>
#include <QDir>

#include <string>

#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief Enumeration containing possible model types and NONE as special absent type.
         */
        enum class ModelTypeTimeDist{
            NONE = 0, TIME_DIST = 1, TIME_DIST_SGV = 2, TIME_DIST_SKIP = 3, TIME_DIST_DUAL = 4
        };

        /**
         * @brief Model Type Names as string, same order as enumeration above to obtain the name of a given enumeration value.
         */
        static const char* ModelTypeTimeDistNames[] = { "None", "Time Dist.", "Time Dist. SGV", "Time Dist. Skip", "Time Dist. Dual"};

        /**
         * @brief The ConfigTimeDist class contains the configuration parameters of Time Dist, as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigTimeDist {
            public:
                /**
                 * @brief Default constructor for class ConfigTimeDist.
                 */
                ConfigTimeDist() = default;

                /**
                 * @brief Get an integer representing a model type (Position in the enum).
                 * @param modelType Model Type that we want to extract the numer (position).
                 * @return Position of the Model Type in the enum.
                 */
                static int ModelTypeTimeDistToInt(ModelTypeTimeDist modelType);

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                /**
                 * @brief Type of model used. (e.g. TimeDist, TimeDistDual...).
                 */
                static ModelTypeTimeDist modelType;

                /**
                 * @brief Size of the population in the Wright Fisher Model (N).
                 */
                static int population_size;

                /**
                 * @brief Selection coefficient (s).
                 */
                static double s;

                /**
                 * @brief Dominance coefficient (h).
                 */
                static double h;

                /**
                 * @brief Backward mutation rate (u).
                 */
                static double u;

                /**
                 * @brief Forward mutation rate (v).
                 */
                static double v;


                /**
                 * @brief No recurrent mutation (m).
                 */
                static bool no_rem;

                /**
                 * @brief Recurrent mutation.
                 */
                static bool rem;

                /**
                 * @brief Tail truncation weight (a).
                 */
                static double a;

                /**
                 * @brief Block Size (b).
                 */
                static int b;

                /**
                 * @brief Maximum number of generations.
                 */
                static int max_t;

                /**
                 * @brief Number of threads for OpenMP (t).
                 */
                static int n_threads;

                /**
                 * @brief Integration Cutoff (c).
                 */
                static double integration_cutoff;

                /**
                 * @brief Path to initial probability distribution CSV (I).
                 */
                static std::string initial_distribution_csv;

                /**
                 * @brief Path output P.
                 */
                static std::string path_output_P;

                /**
                 * @brief Path output Q.
                 */
                static std::string path_output_Q;

                /**
                 * @brief Path output R.
                 */
                static std::string path_output_R;

                /**
                 * @brief Output P.
                 */
                static bool output_P;

                /**
                 * @brief Output Q.
                 */
                static bool output_Q;

                /**
                 * @brief Output R.
                 */
                static bool output_R;

                /**
                 * @brief Output I (Initial probability distribution).
                 */
                static bool output_I;

                /**
                 * @brief Save configuration into a file.
                 */
                static void saveConfigTimeDist();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigTimeDist();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);
        };
    }
}

#endif // CONFIGTIMEDIST_H
