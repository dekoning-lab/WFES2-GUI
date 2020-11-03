#include "imageOutputController.h"

using namespace wfes::controllers;

ImageOutputController::ImageOutputController() : count(0){}

QString ImageOutputController::get_image_I()
{
    if(ImageResults::I == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/I?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_Q()
{
    if(ImageResults::Q == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/Q?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_R()
{
    if(ImageResults::R == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/R?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_B()
{
    if(ImageResults::B == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/B?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_N()
{
    if(ImageResults::N == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/N?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_N_ext()
{
    if(ImageResults::N_ext == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/N_ext?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_N_fix()
{
    if(ImageResults::N_fix == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/N_fix?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_N_tmo()
{
    if(ImageResults::N_tmo == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/N_tmo?count=" + QString(count);
        }
}

QString ImageOutputController::get_image_V()
{
    if(ImageResults::V == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/V?count=" + QString(count);
    }
}

QString ImageOutputController::get_image_E()
{
    if(ImageResults::E == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/E?count=" + QString(count);
    }
}
