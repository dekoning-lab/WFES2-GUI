#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "utils/types.h"

namespace wfes {
    namespace config {

        enum ModelType{
            NONE, ABSORPTION, FIXATION, ESTABLISHMENT, FUNDAMENTAL, EQUILIBRIUM, NON_ABSORBING, ALLELE_AGE
        };
        static const char* ModelTypeNames[] = { "None", "Absorption", "Fixation", "Establishment", "Fundamental", "Equilibrium", "Non Absorbing", "Allele Age"};

        class Config {
            public:
                Config();

                static std::string library;

                static ModelType modelType;

                static llong population_size;

                // Selection coefficients.
                static double s;

                static double h;

                static double u;

                static double v;

                static double no_rem;

                static double rem;

                static double a;

                static llong b;

                static llong n_threads;

                static double integration_cutoff;

                static std::string initial_distribution_csv;

                static llong starting_copies;

                static llong observed_copies;

                static double odds_ratio;

                static std::string path_output_Q;
                static std::string path_output_R;
                static std::string path_output_N;

                static std::string path_output_N_ext;

                static std::string path_output_N_fix;

                static std::string path_output_B;
                static std::string path_output_I;
                static std::string path_output_E;
                static std::string path_output_V;
                static std::string path_output_Res;

                static bool output_Q;
                static bool output_R;
                static bool output_N;
                static bool output_N_ext;
                static bool output_N_fix;
                static bool output_B;
                static bool output_I;
                static bool output_E;
                static bool output_V;
                static bool output_Res;

                static bool force;
                static bool verbose;
                static bool help;

                static std::string error;
        };
    }
}

#endif // CONFIG_H
