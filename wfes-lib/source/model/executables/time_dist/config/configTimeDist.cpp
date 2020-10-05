#include "configTimeDist.h"

using namespace wfes::config;

ConfigTimeDist::ConfigTimeDist() {}

ModelTypeTimeDist ConfigTimeDist::modelType = ModelTypeTimeDist::TIME_DIST;
int ConfigTimeDist::population_size = 10000;
double ConfigTimeDist::s = 0.005;
double ConfigTimeDist::h = 0.5;
double ConfigTimeDist::u = 1.2e-8;
double ConfigTimeDist::v = 1.2e-8;
bool ConfigTimeDist::no_rem = false;
bool ConfigTimeDist::rem = !ConfigTimeDist::no_rem;
double ConfigTimeDist::a = 1e-20;
int ConfigTimeDist::b = 100;
int ConfigTimeDist::max_t = 100000;

int ConfigTimeDist::n_threads = 1;
double ConfigTimeDist::integration_cutoff = 1e-10;
bool ConfigTimeDist::verbose = false;

std::string ConfigTimeDist::initial_distribution_csv = "";
std::string ConfigTimeDist::path_output_P = "output_P.csv";
std::string ConfigTimeDist::path_output_Q = "output_Q.csv";
std::string ConfigTimeDist::path_output_R = "output_R.csv";

bool ConfigTimeDist::output_P = false;
bool ConfigTimeDist::output_Q = false;
bool ConfigTimeDist::output_R = false;
bool ConfigTimeDist::output_I = false;
