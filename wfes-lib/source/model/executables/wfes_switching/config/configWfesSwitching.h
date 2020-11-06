#ifndef CONFIGWFESSWITCHING_H
#define CONFIGWFESSWITCHING_H

#include <string>
#include "utils/types.h"

#include <QDir>
#include <QStandardPaths>
#include <QDebug>

#include <QString>

namespace wfes {
    namespace config {

        /**
         * @brief Enumeration containing possible model types and NONE as special absent type.
         */
        enum class ModelTypeWfesSwitching{
            NONE = 0, FIXATION = 1, ABSORPTION = 2
        };

        /**
         * @brief Model Type Names as string, same order as enumeration above to obtain the name of a given enumeration value.
         */
        static const char* ModelTypeWfesSwitchingNames[] = { "None", "Fixation", "Absorption"};

        class ConfigWfesSwitching {
        public:
            /**
             * @brief Default constructor for class ConfigWfesSwitching.
             */
            ConfigWfesSwitching();

            /**
             * @brief Get integer position of the enumeration value.
             * @param modelType Modeltype to test position.
             * @return Position of modelType in enumaration.
             */
            static int ModelTypeWfesSwitchingToInt(ModelTypeWfesSwitching modelType);

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
            static ModelTypeWfesSwitching modelType;

            static lvec N;

            static dmat r;

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


            static void saveConfigWfesSwitching();

            static void loadConfigWfesSwitching();

            static void processLine(QString line);


        };
    }
}

#endif // CONFIGWFESSWITCHING_H
