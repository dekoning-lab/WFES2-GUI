#ifndef CONFIGWFESSEQUENTIAL_H
#define CONFIGWFESSEQUENTIAL_H

#include "utils/types.h"

namespace wfes {
    namespace config {

        class ConfigWfesSequential {
            public:
                /**
                 * @brief Default constructor for class ConfigWfesSequential.
                 */
                ConfigWfesSequential();

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                static lvec N;

                static dvec t;

                static dvec p;

                static dvec s;

                static dvec h;

                static dvec u;

                static dvec v;

                static double a;

                static double c;

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

#endif // CONFIGWFESSEQUENTIAL_H
