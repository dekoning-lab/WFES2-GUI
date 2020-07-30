#include "config.h"

using namespace wfes::config;

std::string Config::library = "Pardiso";
ModelType Config::modelType = ModelType::ABSORTION;
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

llong Config::observed_copies = 0;
bool Config::observed_copies_b = false;

std::string Config::initial_distribution_csv = "";
std::string Config::output_Q = "";
std::string Config::output_R = "";
std::string Config::output_N = "";
std::string Config::output_N_ext = "";
std::string Config::output_N_fix = "";
std::string Config::output_B = "";
std::string Config::output_I = "";
std::string Config::output_E = "";
std::string Config::output_V = "";

bool Config::csv = false;
bool Config::force = false;
bool Config::verbose = true;
bool Config::help = false;

Config::Config() {
}

