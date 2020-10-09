#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "utils/types.h"

namespace wfes {
    namespace config {

        /**
         * @brief Enumeration containing possible model types and NONE as special absent type.
         */
        enum class ModelTypeWfesSingle{
            NONE = 0, ABSORPTION = 1, FIXATION = 2, ESTABLISHMENT = 3, FUNDAMENTAL = 4, EQUILIBRIUM = 5, NON_ABSORBING = 6, ALLELE_AGE = 7
        };

        /**
         * @brief Model Type Names as string, same order as enumeration above to obtain the name of a given enumeration value.
         */
        static const char *ModelTypeNames[] = { "None", "Absorption", "Fixation", "Establishment", "Fundamental", "Equilibrium", "Non Absorbing", "Allele Age"};

        class ConfigWfesSingle {
            public:
                /**
                 * @brief Default constructor for class Config.
                 */
                ConfigWfesSingle();

                static int ModelTypeWfesSingleToInt(ModelTypeWfesSingle modelType);
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
                static ModelTypeWfesSingle modelType;

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
                 * @brief Starting number of copies - no integration (p).
                 */
                static int starting_copies;

                /**
                 * @brief Observed number of copies (--allele-age only) (x).
                 */
                static int observed_copies;

                /**
                 * @brief Odds ratio (--establishment only) (k).
                 */
                static double odds_ratio;

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
                 * @brief Path output N_Ext (extinction-conditional sojourn).
                 */
                static std::string path_output_N_ext;

                /**
                 * @brief Path output N_fix (fixation-conditional sojourn).
                 */
                static std::string path_output_N_fix;

                /**
                 * @brief Path output B.
                 */
                static std::string path_output_B;

                /**
                 * @brief Path output I (Initial probability distribution).
                 */
                static std::string path_output_I;

                /**
                 * @brief Path output E (Equilibrium frequencies) (Equilibrium mode only).
                 */
                static std::string path_output_E;

                /**
                 * @brief Path output V (Variance time matrix) (Fundamental mode only).
                 */
                static std::string path_output_V;

                /**
                 * @brief Path output Res (Generated results).
                 */
                static std::string path_output_Res;

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
                 * @brief output N_Ext (extintion-conditional sojourn).
                 */
                static bool output_N_ext;

                /**
                 * @brief Path output N_fix (fixation-conditional sojourn).
                 */
                static bool output_N_fix;

                /**
                 * @brief Output B.
                 */
                static bool output_B;

                /**
                 * @brief Output I (Initial probability distribution).
                 */
                static bool output_I;

                /**
                 * @brief Output E (Equilibrium frequencies) (Equilibrium mode only).
                 */
                static bool output_E;

                /**
                 * @brief Output V (Variance time matrix) (Fundamental mode only).
                 */
                static bool output_V;

                /**
                 * @brief Output Res (Generated results).
                 */
                static bool output_Res;

                /**
                 * @brief Do not perform parameter checks.
                 */
                static bool force;

                /**
                 * @brief Verbose solver output (TODO Not Used In GUI.)
                 */
                static bool verbose;

                /**
                 * @brief TODO Not used.
                 */
                static bool help;

                /**
                 * @brief Error messages to show if there is an error.
                 */
                static std::string error;

                /**
                 * @brief Save matrix I (Initial probability distribution) as image for visualization.
                 */
                static bool saveImageI;

                /**
                 * @brief Save matrix Q as image for visualization.
                 */
                static bool saveImageQ;

                /**
                 * @brief Save matrix R as image for visualization.
                 */
                static bool saveImageR;

                /**
                 * @brief Save matrix N as image for visualization.
                 */
                static bool saveImageN;

                /**
                 * @brief Save matrix N_Ext (extintion-conditional sojourn) as image for visualization.
                 */
                static bool saveImageNExt;

                /**
                 * @brief Save matrix N_fix (fixation-conditional sojourn) as image for visualization.
                 */
                static bool saveImageNFix;

                /**
                 * @brief Save matrix B as image for visualization.
                 */
                static bool saveImageB;

                /**
                 * @brief Save matrix V (Variance time matrix) as image for visualization (Fundamental mode only).
                 */
                static bool saveImageV;

                /**
                 * @brief Save matrix E (Equilibrium frequencies) as image for visualization (Equilibrium mode only).
                 */
                static bool saveImageE;

        };
    }
}

#endif // CONFIG_H
