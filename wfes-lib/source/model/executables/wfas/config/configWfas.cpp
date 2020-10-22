#include "configWfas.h"

using namespace wfes::config;

ConfigWfas::ConfigWfas() {}

lvec ConfigWfas::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

lvec ConfigWfas::G = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfas::f = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfas::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfas::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfas::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfas::h = [] {
    dvec tmp(1);
    tmp << 0.6;
    return tmp;
}();

std::string ConfigWfas::library = "Pardiso";
std::string ConfigWfas::vienna_solver = "BicGStab";

double ConfigWfas::a = 1e-20;
int ConfigWfas::p = 1;
int ConfigWfas::n_threads = 1;
bool ConfigWfas::no_proj = false;

bool ConfigWfas::output_Q = false;
bool ConfigWfas::output_R = false;
bool ConfigWfas::output_N = false;
bool ConfigWfas::output_B = false;
bool ConfigWfas::output_N_Ext = false;
bool ConfigWfas::output_N_Fix = false;
bool ConfigWfas::output_N_Tmo = false;
bool ConfigWfas::output_Dist = true;

std::string ConfigWfas::initial_distribution_csv = "";
std::string ConfigWfas::path_output_Q = "output_Q.csv";
std::string ConfigWfas::path_output_R = "output_R.csv";
std::string ConfigWfas::path_output_N = "output_N.csv";
std::string ConfigWfas::path_output_B = "output_B.csv";
std::string ConfigWfas::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfas::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfas::path_output_N_Tmo = "output_N_Tmo.csv";
std::string ConfigWfas::path_output_Dist = "output_Dist.csv";

bool ConfigWfas::force = false;
bool ConfigWfas::verbose = false;
std::string ConfigWfas::error = "";
int ConfigWfas::num_comp = 1;
