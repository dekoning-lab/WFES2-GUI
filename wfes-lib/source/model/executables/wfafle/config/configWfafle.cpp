#include "configWfafle.h"

using namespace wfes::config;

ConfigWfafle::ConfigWfafle() {}

ivec ConfigWfafle::N = [] {
    ivec tmp(2);
    tmp << 100, 100;
    return tmp;
}();

ivec ConfigWfafle::G = [] {
    ivec tmp(2);
    tmp << 100, 100;
    return tmp;
}();

dvec ConfigWfafle::u = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigWfafle::v = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigWfafle::s = [] {
    dvec tmp(2);
    tmp << 0, 0;
    return tmp;
}();

dvec ConfigWfafle::h = [] {
    dvec tmp(2);
    tmp << 0.5, 0.5;
    return tmp;
}();

std::string ConfigWfafle::library = "Pardiso";
std::string ConfigWfafle::vienna_solver = "BicGStab";

double ConfigWfafle::a = 1e-20;
int ConfigWfafle::p = 1;
int ConfigWfafle::n_threads = 1;

bool ConfigWfafle::output_I = false;
bool ConfigWfafle::output_Res = true;

std::string ConfigWfafle::initial_distribution_csv = "";
std::string ConfigWfafle::path_output_I = "output_I.csv";
std::string ConfigWfafle::path_output_Res = "output_Res.csv";

bool ConfigWfafle::force = false;
bool ConfigWfafle::verbose = false;
std::string ConfigWfafle::error = "";
int ConfigWfafle::num_comp = 2;
