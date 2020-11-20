#ifndef IMAGERESULTS_H
#define IMAGERESULTS_H

#include <QImage>

class ImageResults
{
public:
    /**
     * @brief Reference to image I
     */
    static QImage *I;
    /**
     * @brief Reference to image Q
     */
    static QImage *Q;
    /**
     * @brief Reference to image R
     */
    static QImage *R;
    /**
     * @brief Reference to image N
     */
    static QImage *N;
    /**
     * @brief Reference to image N_Ext
     */
    static QImage *N_ext;
    /**
     * @brief Reference to image N_fix
     */
    static QImage *N_fix;
    /**
     * @brief Reference to image N_tmo
     */
    static QImage *N_tmo;
    /**
     * @brief Reference to image B
     */
    static QImage *B;
    /**
     * @brief Reference to image V
     */
    static QImage *V;
    /**
     * @brief Reference to image E
     */
    static QImage *E;
    /**
     * @brief Reference to image P
     */
    static QImage *P;

    /**
     * @brief ImageResults constructor.
     */
    ImageResults() = default;

    /**
     * @brief Return an image by name.
     * @param id Name of the image.
     * @return QImage requested.
     */
    static QImage getImage(QString id);

    /**
     * @brief Remove all images.
     */
    static void clear();

};

#endif // IMAGERESULTS_H
