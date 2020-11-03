#ifndef IMAGEOUTPUTCONTROLLER_H
#define IMAGEOUTPUTCONTROLLER_H

#include <QObject>
#include "imageresults.h"

namespace wfes {
    namespace controllers {
        class ImageOutputController :public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_image_I READ get_image_I NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_Q READ get_image_Q NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_R READ get_image_R NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_B READ get_image_B NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_N READ get_image_N NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_N_ext READ get_image_N_ext NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_N_fix READ get_image_N_fix NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_N_tmo READ get_image_N_tmo NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_V READ get_image_V NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_E READ get_image_E NOTIFY image_changed)

            public:
                int count;
                QString get_image_I();
                QString get_image_Q();
                QString get_image_R();
                QString get_image_B();
                QString get_image_N();
                QString get_image_N_ext();
                QString get_image_N_fix();
                QString get_image_N_tmo();
                QString get_image_V();
                QString get_image_E();

                ImageOutputController();

            signals:
                void image_changed();
        };
    }
}

#endif // IMAGEOUTPUTCONTROLLER_H
