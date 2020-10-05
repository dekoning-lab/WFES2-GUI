#include "configWfesSingle.h"

using namespace wfes::config;

std::string ConfigWfesSingle::library = "ViennaCL";
std::string ConfigWfesSingle::vienna_solver = "BicGStab";
ModelType ConfigWfesSingle::modelType = ModelType::ABSORPTION;
int ConfigWfesSingle::population_size = 10000;
double ConfigWfesSingle::s = 0.005;
double ConfigWfesSingle::h = 0.5;
double ConfigWfesSingle::u = 1.2e-8;
double ConfigWfesSingle::v = 1.2e-8;
bool ConfigWfesSingle::no_rem = false;
bool ConfigWfesSingle::rem = !ConfigWfesSingle::no_rem;
double ConfigWfesSingle::a = 1e-20;
double ConfigWfesSingle::odds_ratio = 1.0;
int ConfigWfesSingle::b = 100;
int ConfigWfesSingle::n_threads = 1;
double ConfigWfesSingle::integration_cutoff = 1e-10;
int ConfigWfesSingle::starting_copies = 0;

int ConfigWfesSingle::observed_copies = 1;

std::string ConfigWfesSingle::initial_distribution_csv = "";
std::string ConfigWfesSingle::path_output_Q = "output_Q.csv";
std::string ConfigWfesSingle::path_output_R = "output_R.csv";
std::string ConfigWfesSingle::path_output_N = "output_N.csv";
std::string ConfigWfesSingle::path_output_N_ext = "output_N_ext.csv";
std::string ConfigWfesSingle::path_output_N_fix = "output_N_fix.csv";
std::string ConfigWfesSingle::path_output_B = "output_B.csv";
std::string ConfigWfesSingle::path_output_I = "output_I.csv";
std::string ConfigWfesSingle::path_output_E = "output_E.csv";
std::string ConfigWfesSingle::path_output_V = "output_V.csv";
std::string ConfigWfesSingle::path_output_Res = "output_Res.csv";

bool ConfigWfesSingle::output_Q = false;
bool ConfigWfesSingle::output_R = false;
bool ConfigWfesSingle::output_N = false;
bool ConfigWfesSingle::output_N_ext = false;
bool ConfigWfesSingle::output_N_fix = false;
bool ConfigWfesSingle::output_B = false;
bool ConfigWfesSingle::output_I = false;
bool ConfigWfesSingle::output_E = false;
bool ConfigWfesSingle::output_V = false;
bool ConfigWfesSingle::output_Res = true;

bool ConfigWfesSingle::force = false;
bool ConfigWfesSingle::verbose = false;
bool ConfigWfesSingle::help = false;

bool ConfigWfesSingle::saveImageI = false;
bool ConfigWfesSingle::saveImageQ = false;
bool ConfigWfesSingle::saveImageR = false;
bool ConfigWfesSingle::saveImageN = false;
bool ConfigWfesSingle::saveImageNExt = false;
bool ConfigWfesSingle::saveImageNFix = false;
bool ConfigWfesSingle::saveImageB = false;
bool ConfigWfesSingle::saveImageV = false;
bool ConfigWfesSingle::saveImageE = false;

std::string ConfigWfesSingle::error = "";

ConfigWfesSingle::ConfigWfesSingle() {
}


int ConfigWfesSingle::ModelTypeWfesSingleToInt(ModelType modelType){
    switch(modelType){
    case ModelType::ABSORPTION:
        return 1;
    case ModelType::FIXATION:
        return 2;
    case ModelType::ESTABLISHMENT:
        return 3;
    case ModelType::FUNDAMENTAL:
        return 4;
    case ModelType::EQUILIBRIUM:
        return 5;
    case ModelType::NON_ABSORBING:
        return 6;
    case ModelType::ALLELE_AGE:
        return 7;
    case ModelType::NONE:
    default:
        return 0;
    }
}

