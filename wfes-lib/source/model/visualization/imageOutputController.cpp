#include "imageOutputController.h"

using namespace wfes::controllers;

ImageOutputController::ImageOutputController(QObject* parent) : QObject(parent), count(0){}

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

QString ImageOutputController::get_image_P()
{
    if(ImageResults::P == nullptr)
        return "image://visualizationImageProvider/null";
    else {
        count++;
        return "image://visualizationImageProvider/P?count=" + QString(count);
    }
}

void ImageOutputController::set_image_to_download(QString imageName)
{
    this->image_to_download = imageName;
}

QString ImageOutputController::download()
{

    //TODO put outputPath in global configuration.
    QString outputPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Wfes/");
    QDir dir;

    if (!dir.exists(outputPath))
        dir.mkpath(outputPath);

    if(this->image_to_download.compare("I") == 0)
        utils::saveImage(ImageResults::I, (outputPath + QString::fromStdString("Image_-_I")).toStdString());
    else if(this->image_to_download.compare("Q") == 0)
        utils::saveImage(ImageResults::Q, (outputPath + QString::fromStdString("Image_-_Q")).toStdString());
    else if(this->image_to_download.compare("R") == 0)
        utils::saveImage(ImageResults::R, (outputPath + QString::fromStdString("Image_-_R")).toStdString());
    else if(this->image_to_download.compare("B") == 0)
        utils::saveImage(ImageResults::B, (outputPath + QString::fromStdString("Image_-_B")).toStdString());
    else if(this->image_to_download.compare("N") == 0)
        utils::saveImage(ImageResults::N, (outputPath + QString::fromStdString("Image_-_N")).toStdString());
    else if(this->image_to_download.compare("N_ext") == 0)
        utils::saveImage(ImageResults::N_ext, (outputPath + QString::fromStdString("Image_-_N_ext")).toStdString());
    else if(this->image_to_download.compare("N_fix") == 0)
        utils::saveImage(ImageResults::N_fix, (outputPath + QString::fromStdString("Image_-_N_fix")).toStdString());
    else if(this->image_to_download.compare("N_tmo") == 0)
        utils::saveImage(ImageResults::N_tmo, (outputPath + QString::fromStdString("Image_-_N_tmo")).toStdString());
    else if(this->image_to_download.compare("V") == 0)
        utils::saveImage(ImageResults::V, (outputPath + QString::fromStdString("Image_-_V")).toStdString());
    else if(this->image_to_download.compare("E") == 0)
        utils::saveImage(ImageResults::E, (outputPath + QString::fromStdString("Image_-_E")).toStdString());
    else if(this->image_to_download.compare("P") == 0)
        utils::saveImage(ImageResults::P, (outputPath + QString::fromStdString("Image_-_P")).toStdString());

    return "";
}
