#include "configWfesSequential.h"

using namespace wfes::config;

ConfigWfesSequential::ConfigWfesSequential() {}

lvec ConfigWfesSequential::N = [] {
    lvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSequential::t = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSequential::p = [] {
    dvec tmp(1);
    tmp << 100;
    return tmp;
}();

dvec ConfigWfesSequential::u = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSequential::v = [] {
    dvec tmp(1);
    tmp << 1e-9;
    return tmp;
}();

dvec ConfigWfesSequential::s = [] {
    dvec tmp(1);
    tmp << 0;
    return tmp;
}();

dvec ConfigWfesSequential::h = [] {
    dvec tmp(1);
    tmp << 0.6;
    return tmp;
}();

std::string ConfigWfesSequential::library = "Pardiso";
std::string ConfigWfesSequential::vienna_solver = "BicGStab";

double ConfigWfesSequential::a = 1e-20;
double ConfigWfesSequential::c = 1e-10;
int ConfigWfesSequential::n_threads = 1;


bool ConfigWfesSequential::output_Q = false;
bool ConfigWfesSequential::output_R = false;
bool ConfigWfesSequential::output_N = false;
bool ConfigWfesSequential::output_B = false;
bool ConfigWfesSequential::output_I = false;
bool ConfigWfesSequential::output_N_Fix = false;
bool ConfigWfesSequential::output_N_Ext = false;
bool ConfigWfesSequential::output_N_Tmo = false;
bool ConfigWfesSequential::output_Res = true;

std::string ConfigWfesSequential::initial_distribution_csv = "";
std::string ConfigWfesSequential::path_output_Q = "output_Q.csv";
std::string ConfigWfesSequential::path_output_R = "output_R.csv";
std::string ConfigWfesSequential::path_output_N = "output_N.csv";
std::string ConfigWfesSequential::path_output_B = "output_B.csv";
std::string ConfigWfesSequential::path_output_I = "output_I.csv";
std::string ConfigWfesSequential::path_output_N_Ext = "output_N_Ext.csv";
std::string ConfigWfesSequential::path_output_N_Fix = "output_N_Fix.csv";
std::string ConfigWfesSequential::path_output_N_Tmo = "output_N_Tmo.csv";
std::string ConfigWfesSequential::path_output_Res = "output_Res.csv";

bool ConfigWfesSequential::force = false;
bool ConfigWfesSequential::verbose = false;
std::string ConfigWfesSequential::error = "";
int ConfigWfesSequential::num_comp = 1;


