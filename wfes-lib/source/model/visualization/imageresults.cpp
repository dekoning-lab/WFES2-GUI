#include "imageresults.h"

QImage* ImageResults::I = nullptr;
QImage* ImageResults::Q = nullptr;
QImage* ImageResults::R = nullptr;
QImage* ImageResults::N = nullptr;
QImage* ImageResults::N_ext = nullptr;
QImage* ImageResults::N_fix = nullptr;
QImage* ImageResults::N_tmo = nullptr;
QImage* ImageResults::B = nullptr;
QImage* ImageResults::V = nullptr;
QImage* ImageResults::E = nullptr;
QImage* ImageResults::P = nullptr;

ImageResults::ImageResults() {}

QImage ImageResults::getImage(QString id)
{
    if(id.compare("I") == 0 && ImageResults::I != nullptr)
        return *ImageResults::I;
    if(id.compare("Q") == 0 && ImageResults::Q != nullptr)
        return *ImageResults::Q;
    if(id.compare("R") == 0 && ImageResults::R != nullptr)
        return *ImageResults::R;
    if(id.compare("N") == 0 && ImageResults::N != nullptr)
        return *ImageResults::N;
    if(id.compare("N_ext") == 0 && ImageResults::N_ext != nullptr)
        return *ImageResults::N_ext;
    if(id.compare("N_fix") == 0 && ImageResults::N_fix != nullptr)
        return *ImageResults::N_fix;
    if(id.compare("N_tmo") == 0 && ImageResults::N_tmo != nullptr)
        return *ImageResults::N_tmo;
    if(id.compare("B") == 0 && ImageResults::B != nullptr)
        return *ImageResults::B;
    if(id.compare("V") == 0 && ImageResults::V != nullptr)
        return *ImageResults::V;
    if(id.compare("E") == 0 && ImageResults::E != nullptr)
        return *ImageResults::E;
    if(id.compare("P") == 0 && ImageResults::P != nullptr)
        return *ImageResults::P;
    else {
        QImage image(100, 100, QImage::Format_ARGB32);
        image.fill(Qt::white);
        return image;
    }
}

void ImageResults::clear()
{
    ImageResults::I = nullptr;
    ImageResults::Q = nullptr;
    ImageResults::R = nullptr;
    ImageResults::N = nullptr;
    ImageResults::N_ext = nullptr;
    ImageResults::N_fix = nullptr;
    ImageResults::N_tmo = nullptr;
    ImageResults::B = nullptr;
    ImageResults::V = nullptr;
    ImageResults::E = nullptr;
    ImageResults::P = nullptr;
}
