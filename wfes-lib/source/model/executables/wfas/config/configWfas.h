#ifndef CONFIGWFAS_H
#define CONFIGWFAS_H

#include <string>
#include "utils/types.h"

#include <QString>

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

namespace wfes {
    namespace config {

        class ConfigWfas {
            public:
                /**
                 * @brief Default constructor for class ConfigWfas.
                 */
                ConfigWfas();

                /**
                 * @brief Library used for solving matrix systems (e.g. pardiso, viennacl...).
                 */
                static std::string library;

                /**
                 * @brief Solver used in viennacl. (e.g. biCGStab, GMRes...).
                 */
                static std::string vienna_solver;

                /**
                 * @brief Population size for each of the k epochs (N)
                 */
                static lvec N;

                /**
                 * @brief Number of generations each of the k epochs last (G)
                 */
                static lvec G;

                /**
                 * @brief Approximating (down) factor for each population size (f).
                 */
                static dvec f;

                /**
                 * @brief Individial selection coefficient (s)
                 */
                static dvec s;

                static dvec h;

                static dvec u;

                static dvec v;

                static double a;

                /**
                 * @brief p Initial number of alleles (i will be ignored)
                 */
                static int p;

                static int n_threads;

                /**
                 * @brief no_proj Do not project the distribution down.
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
                 * @brief Output Res (Generated results).
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

                static void saveConfigWfas();

                static void loadConfigWfas();

                static void processLine(QString line);
            };
    }
}

#endif // CONFIGWFAS_H
