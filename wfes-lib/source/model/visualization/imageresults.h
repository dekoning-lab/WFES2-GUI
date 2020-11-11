#ifndef IMAGERESULTS_H
#define IMAGERESULTS_H

#include <QImage>

class ImageResults
{
public:
    static QImage *I;
    static QImage *Q;
    static QImage *R;
    static QImage *N;
    static QImage *N_ext;
    static QImage *N_fix;
    static QImage *N_tmo;
    static QImage *B;
    static QImage *V;
    static QImage *E;
    static QImage *P;

    ImageResults();

    static QImage getImage(QString id);

    static void clear();

};

#endif // IMAGERESULTS_H
