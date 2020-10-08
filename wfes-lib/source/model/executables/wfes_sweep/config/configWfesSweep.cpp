#include "configWfesSweep.h"


using namespace wfes::config;

ivec ConfigWfesSweep::population_sizes = [] {
    ivec tmp(2);
    tmp << 10000, 10000;
    return tmp;
}();

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

ConfigWfesSweep::ConfigWfesSweep() {}
