#include "configTimeDistSGV.h"

using namespace wfes::config;

dvec ConfigTimeDistSGV::u = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigTimeDistSGV::v = [] {
    dvec tmp(2);
    tmp << 1e-9, 1e-9;
    return tmp;
}();

dvec ConfigTimeDistSGV::s = [] {
    dvec tmp(2);
    tmp << 0, 0;
    return tmp;
}();

dvec ConfigTimeDistSGV::h = [] {
    dvec tmp(2);
    tmp << 0.5, 0.5;
    return tmp;
}();


double ConfigTimeDistSGV::l = 1e-20;

bool ConfigTimeDistSGV::force = false;

ConfigTimeDistSGV::ConfigTimeDistSGV(){}
