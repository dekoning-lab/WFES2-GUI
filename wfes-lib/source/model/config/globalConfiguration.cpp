#include "globalConfiguration.h"

using namespace wfes::controllers;

bool GlobalConfiguration::generateImages = false;

bool GlobalConfiguration::getGenerateImages() {
    return GlobalConfiguration::generateImages;
}

void GlobalConfiguration::setGenerateImages(bool generate) {
    GlobalConfiguration::generateImages = generate;
}
