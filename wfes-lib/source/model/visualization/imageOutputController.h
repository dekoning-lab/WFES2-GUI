#ifndef IMAGEOUTPUTCONTROLLER_H
#define IMAGEOUTPUTCONTROLLER_H

#include <QObject>
namespace wfes {
    namespace controllers {
        class ImageOutputController :public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString ui_image_source READ get_image_source NOTIFY image_changed)

            public:
                int count;
                QString get_image_source();

                ImageOutputController();

            signals:
                void image_changed();
        };
    }
}

#endif // IMAGEOUTPUTCONTROLLER_H
