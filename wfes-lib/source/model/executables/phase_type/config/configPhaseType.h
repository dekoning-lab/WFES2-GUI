#ifndef CONFIGPHASETYPE_H
#define CONFIGPHASETYPE_H

#include <QStandardPaths>
#include <QString>
#include <QDebug>
#include <QDir>

#include <string>

#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief Enumeration containing possible model types and NONE as special absent type.
         */
        enum class ModelTypePhaseType{
            NONE = 0, PHASE_TYPE_DIST = 1, PHASE_TYPE_MOMENTS = 2
        };

        /**
         * @brief Model Type Names as string, same order as enumeration above to obtain the name of a given enumeration value.
         */
        static const char *ModelTypePhaseTypeNames[] = { "None", "Phase Type Dist.", "Phase Type Moments"};

        /**
         * @brief The ConfigPhaseType class contains the configuration parameters of Phase Type, as well as some functions for
         * saving and loading the configuration.
         */
        class ConfigPhaseType {
            public:
                /**
                 * @brief Default constructor for class ConfigPhaseType.
                 */
                ConfigPhaseType() = default;

                /**
                 * @brief Get an integer representing a model type (Position in the enum).
                 * @param modelType Model Type that we want to extract the numer (position).
                 * @return Position of the Model Type in the enum.
                 */
                static int ModelTypePhaseTypeToInt(ModelTypePhaseType modelType);

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                /**
                 * @brief Type of model used. (e.g. Fixation, Absorption...).
                 */
                static enum ModelTypePhaseType modelType;

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
                 * @brief Number of moments (k).
                 */
                static int k;

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
                 * @brief Odds ratio (--establishment only) (k).
                 */
                static double odds_ratio;

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
                 * @brief Path output Moments.
                 */
                static std::string path_output_Moments;

                /**
                 * @brief Path output Res (Generated results).
                 */
                static std::string path_output_Res;

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
                 * @brief Output Moments.
                 */
                static bool output_Moments;

                /**
                 * @brief Output Res (Generated results).
                 */
                static bool output_Res;

                /**
                 * @brief Do not perform parameter checks.
                 */
                static bool force;

                /**
                 * @brief Save configuration into a file.
                 */
                static void saveConfigPhaseType();

                /**
                 * @brief Load configuration from a file.
                 */
                static void loadConfigPhaseType();

                /**
                 * @brief Process a line from the configuration file.
                 * @param line Current line being processed in the configuration file.
                 */
                static void processLine(QString line);
        };
    }
}


#endif // CONFIGPHASETYPE_H
