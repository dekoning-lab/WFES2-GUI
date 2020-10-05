#include "configWfesSingle.h"

using namespace wfes::config;

std::string Config::library = "ViennaCL";
std::string Config::vienna_solver = "BicGStab";
ModelType Config::modelType = ModelType::ABSORPTION;
int Config::population_size = 10000;
double Config::s = 0.005;
double Config::h = 0.5;
double Config::u = 1.2e-8;
double Config::v = 1.2e-8;
bool Config::no_rem = false;
bool Config::rem = !Config::no_rem;
double Config::a = 1e-20;
double Config::odds_ratio = 1.0;
int Config::b = 100;
int Config::n_threads = 1;
double Config::integration_cutoff = 1e-10;
int Config::starting_copies = 0;

int Config::observed_copies = 1;

std::string Config::initial_distribution_csv = "";
std::string Config::path_output_Q = "output_Q.csv";
std::string Config::path_output_R = "output_R.csv";
std::string Config::path_output_N = "output_N.csv";
std::string Config::path_output_N_ext = "output_N_ext.csv";
std::string Config::path_output_N_fix = "output_N_fix.csv";
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

bool Config::saveImageI = false;
bool Config::saveImageQ = false;
bool Config::saveImageR = false;
bool Config::saveImageN = false;
bool Config::saveImageNExt = false;
bool Config::saveImageNFix = false;
bool Config::saveImageB = false;
bool Config::saveImageV = false;
bool Config::saveImageE = false;

std::string Config::error = "";

Config::Config() {
}

