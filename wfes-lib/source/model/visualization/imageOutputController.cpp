#include "imageOutputController.h"

using namespace wfes::controllers;

ImageOutputController::ImageOutputController()
{
count = 0;
}

QString ImageOutputController::get_image_source()
{
    count++;
    return "image://visualizationImageProvider/Q?count=" + QString(count);
}
