#include "imageresults.h"

QImage* ImageResults::I = nullptr;
QImage* ImageResults::Q = nullptr;
QImage* ImageResults::R = nullptr;
QImage* ImageResults::N = nullptr;
QImage* ImageResults::N_ext = nullptr;
QImage* ImageResults::N_fix = nullptr;
QImage* ImageResults::B = nullptr;

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
    if(id.compare("B") == 0 && ImageResults::B != nullptr)
        return *ImageResults::B;
    else {
        QImage image(100, 100, QImage::Format_ARGB32);
        image.fill(Qt::red);
        return image;
    }
}
