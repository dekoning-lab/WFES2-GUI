#include "configWfesSwitching.h"

using namespace wfes::config;

ConfigWfesSwitching::ConfigWfesSwitching() {}

int ConfigWfesSwitching::ModelTypeWfesSwitchingToInt(ModelTypeWfesSwitching modelType)
{
    switch(modelType){
        case ModelTypeWfesSwitching::FIXATION:
            return 1;
        case ModelTypeWfesSwitching::ABSORPTION:
            return 2;
        case ModelTypeWfesSwitching::NONE:
        default:
            return 0;
    }
}

lvec ConfigWfesSwitching::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSwitching::r = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSwitching::p = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSwitching::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSwitching::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSwitching::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfesSwitching::h = [] {
    dvec tmp(1);
    tmp << 0.6;
    return tmp;
}();

ModelTypeWfesSwitching ConfigWfesSwitching::modelType = ModelTypeWfesSwitching::ABSORPTION;

std::string ConfigWfesSwitching::library = "Pardiso";
std::string ConfigWfesSwitching::vienna_solver = "BicGStab";

double ConfigWfesSwitching::a = 1e-20;
double ConfigWfesSwitching::c = 1e-10;
int ConfigWfesSwitching::n_threads = 1;


bool ConfigWfesSwitching::output_Q = false;
bool ConfigWfesSwitching::output_R = false;
bool ConfigWfesSwitching::output_N = false;
bool ConfigWfesSwitching::output_B = false;
bool ConfigWfesSwitching::output_I = false;
bool ConfigWfesSwitching::output_N_Fix = false;
bool ConfigWfesSwitching::output_N_Ext = false;
bool ConfigWfesSwitching::output_Res = true;

std::string ConfigWfesSwitching::initial_distribution_csv = "";
std::string ConfigWfesSwitching::path_output_Q = "output_Q.csv";
std::string ConfigWfesSwitching::path_output_R = "output_R.csv";
std::string ConfigWfesSwitching::path_output_N = "output_N.csv";
std::string ConfigWfesSwitching::path_output_B = "output_B.csv";
std::string ConfigWfesSwitching::path_output_I = "output_I.csv";
std::string ConfigWfesSwitching::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfesSwitching::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfesSwitching::path_output_Res = "output_Res.csv";

bool ConfigWfesSwitching::force = false;
bool ConfigWfesSwitching::verbose = false;
std::string ConfigWfesSwitching::error = "";
int ConfigWfesSwitching::num_comp = 1;
