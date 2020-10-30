#include "imageOutputController.h"

using namespace wfes::controllers;

ImageOutputController::ImageOutputController() : count(0){}

QString ImageOutputController::get_image_I()
{
    count++;
    return "image://visualizationImageProvider/I?count=" + QString(count);
}

QString ImageOutputController::get_image_Q()
{
    count++;
    return "image://visualizationImageProvider/Q?count=" + QString(count);
}

QString ImageOutputController::get_image_R()
{
    count++;
    return "image://visualizationImageProvider/R?count=" + QString(count);
}

QString ImageOutputController::get_image_B()
{
    count++;
    return "image://visualizationImageProvider/B?count=" + QString(count);
}

QString ImageOutputController::get_image_N()
{
    count++;
    return "image://visualizationImageProvider/N?count=" + QString(count);
}

QString ImageOutputController::get_image_N_ext()
{
    count++;
    return "image://visualizationImageProvider/N_ext?count=" + QString(count);
}

QString ImageOutputController::get_image_N_fix()
{
    count++;
    return "image://visualizationImageProvider/N_fix?count=" + QString(count);
}
