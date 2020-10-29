#ifndef IMAGERESULTS_H
#define IMAGERESULTS_H

#import <QImage>

class ImageResults
{
public:
    static QImage *I;
    static QImage *Q;
    static QImage *R;
    static QImage *N;
    static QImage *N_ext;
    static QImage *N_fix;
    static QImage *B;

    ImageResults();

    static QImage getImage(QString id);

};

#endif // IMAGERESULTS_H
