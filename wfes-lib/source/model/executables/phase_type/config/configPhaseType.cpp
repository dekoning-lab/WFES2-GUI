#include "configPhaseType.h"

using namespace wfes::config;

ConfigPhaseType::ConfigPhaseType() {}

int ConfigPhaseType::ModelTypePhaseTypeToInt(enum ModelTypePhaseType modelType) {
    switch(modelType){
    case ModelTypePhaseType::PHASE_TYPE_DIST:
        return 1;
    case ModelTypePhaseType::PHASE_TYPE_MOMENTS:
        return 2;
    case ModelTypePhaseType::NONE:
    default:
        return 0;
    }
}


std::string ConfigPhaseType::library = "Pardiso";
std::string ConfigPhaseType::vienna_solver = "BicGStab";
ModelTypePhaseType ConfigPhaseType::modelType = ModelTypePhaseType::PHASE_TYPE_DIST;
int ConfigPhaseType::population_size = 10000;
double ConfigPhaseType::s = 0.005;
double ConfigPhaseType::h = 0.5;
double ConfigPhaseType::u = 1.2e-8;
double ConfigPhaseType::v = 1.2e-8;
bool ConfigPhaseType::no_rem = false;
bool ConfigPhaseType::rem = !ConfigPhaseType::no_rem;
double ConfigPhaseType::a = 1e-20;
double ConfigPhaseType::odds_ratio = 1.0;
int ConfigPhaseType::b = 100;
int ConfigPhaseType::n_threads = 1;
double ConfigPhaseType::integration_cutoff = 1e-10;
std::string ConfigPhaseType::path_output_P = "output_P.csv";
std::string ConfigPhaseType::path_output_Q = "output_Q.csv";
std::string ConfigPhaseType::path_output_R = "output_R.csv";
std::string ConfigPhaseType::path_output_Res = "output_Res.csv";
int ConfigPhaseType::max_t = 100000;
int ConfigPhaseType::k = 20;

bool ConfigPhaseType::output_P = false;
bool ConfigPhaseType::output_Q = false;
bool ConfigPhaseType::output_R = false;
bool ConfigPhaseType::output_Res = true;

bool ConfigPhaseType::force = false;
bool ConfigPhaseType::verbose = false;
bool ConfigPhaseType::help = false;

std::string ConfigPhaseType::error = "";
