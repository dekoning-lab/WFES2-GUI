#include "config.h"

using namespace wfes::config;

std::string Config::library = "Pardiso";
ModelType Config::modelType = ModelType::ABSORPTION;
llong Config::population_size = 10000;
double Config::s = 0.005;
double Config::h = 0.5;
double Config::u = 1.2e-8;
double Config::v = 1.2e-8;
double Config::no_rem = false;
double Config::rem = !Config::no_rem;
double Config::a = 1e-20;
double Config::odds_ratio = 1.0;
llong Config::b = 100;
llong Config::n_threads = 1;
double Config::integration_cutoff = 1e-10;
llong Config::starting_copies = 0;

llong Config::observed_copies = 1;

std::string Config::initial_distribution_csv = "";
std::string Config::path_output_Q = "output_Q.csv";
std::string Config::path_output_R = "output_R.csv";
std::string Config::path_output_N = "output_N.csv";
std::string Config::path_output_N_ext = "";
std::string Config::path_output_N_fix = "";
std::string Config::path_output_B = "output_B.csv";
std::string Config::path_output_I = "output_I.csv";
std::string Config::path_output_E = "output_E.csv";
std::string Config::path_output_V = "output_V.csv";
std::string Config::path_output_Res = "output_Res.csv";

bool Config::output_Q = false;
bool Config::output_R = false;
bool Config::output_N = false;
bool Config::output_N_ext = false;
bool Config::output_N_fix = false;
bool Config::output_B = false;
bool Config::output_I = false;
bool Config::output_E = false;
bool Config::output_V = false;
bool Config::output_Res = true;

bool Config::force = false;
bool Config::verbose = false;
bool Config::help = false;

Config::Config() {
}

