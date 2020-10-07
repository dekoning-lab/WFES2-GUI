#ifndef CONFIGTIMEDIST_H
#define CONFIGTIMEDIST_H

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

        class ConfigTimeDist
        {
        public:
            /**
             * @brief Default constructor for class ConfigTimeDist.
             */
            ConfigTimeDist();

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
             * @brief Starting number of copies integration cutoff (c).
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
             * @brief Verbose solver output (TODO Not Used In GUI.)
             */
            static bool verbose;

            /**
             * @brief Error messages to show if there is an error.
             */
            static std::string error;

        };
    }
}

#endif // CONFIGTIMEDIST_H
