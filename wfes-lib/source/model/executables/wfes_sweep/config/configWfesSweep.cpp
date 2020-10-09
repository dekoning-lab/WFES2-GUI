#include "configWfesSweep.h"


using namespace wfes::config;

ConfigWfesSweep::ConfigWfesSweep() {}

int ConfigWfesSweep::ModelTypeWfesSweepToInt(ModelTypeWfesSweep modelType)
{
    switch(modelType){
        case ModelTypeWfesSweep::FIXATION:
            return 1;
        case ModelTypeWfesSweep::NONE:
        default:
            return 0;
    }
}

ModelTypeWfesSweep ConfigWfesSweep::modelType = ModelTypeWfesSweep::FIXATION;
std::string ConfigWfesSweep::library = "ViennaCL";
std::string ConfigWfesSweep::vienna_solver = "BicGStab";
double ConfigWfesSweep::a = 1e-20;
int ConfigWfesSweep::b = 100;
int ConfigWfesSweep::n_threads = 1;
double ConfigWfesSweep::integration_cutoff = 1 - 1e-8;
double ConfigWfesSweep::l = 1e-20;

bool ConfigWfesSweep::output_Q = false;
bool ConfigWfesSweep::output_R = false;
bool ConfigWfesSweep::output_N = false;
bool ConfigWfesSweep::output_B = false;
bool ConfigWfesSweep::output_I = false;
bool ConfigWfesSweep::output_Res = true;

std::string ConfigWfesSweep::initial_distribution_csv = "";
std::string ConfigWfesSweep::path_output_Q = "output_Q.csv";
std::string ConfigWfesSweep::path_output_R = "output_R.csv";
std::string ConfigWfesSweep::path_output_N = "output_N.csv";
std::string ConfigWfesSweep::path_output_B = "output_B.csv";
std::string ConfigWfesSweep::path_output_I = "output_I.csv";
std::string ConfigWfesSweep::path_output_Res = "output_Res.csv";

bool ConfigWfesSweep::force = false;
bool ConfigWfesSweep::verbose = false;

int ConfigWfesSweep::population_size = 10000;

ivec ConfigWfesSweep::starting_copies = [] {
    ivec tmp(2);
    tmp << 0, 0;
    return tmp;
}();

dvec ConfigWfesSweep::u = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigWfesSweep::v = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigWfesSweep::s = [] {
    dvec tmp(2);
    tmp << 0, 0;
    return tmp;
}();

dvec ConfigWfesSweep::h = [] {
    dvec tmp(2);
    tmp << 0.5, 0.5;
    return tmp;
}();

