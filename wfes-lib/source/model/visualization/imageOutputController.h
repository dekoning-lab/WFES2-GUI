#ifndef IMAGEOUTPUTCONTROLLER_H
#define IMAGEOUTPUTCONTROLLER_H

#include <wfes-lib_global.h>
#include <QObject>
#include "imageresults.h"
#include "utils/utils.h"

namespace wfes {
    namespace controllers {

        /**
         * @brief The ImageOutputController class allows visualization of matrices and vectors
         * as images in GUI.
         */
        class WFESLIBSHARED_EXPORT ImageOutputController :public QObject {
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
            Q_PROPERTY(QString ui_image_P READ get_image_P NOTIFY image_changed)
            Q_PROPERTY(QString ui_image_to_download WRITE set_image_to_download)
            Q_PROPERTY(QString ui_download READ download CONSTANT)

            public:
                /**
                 * @brief Number for changing the uri of the image, so it is recognized as new.
                 */
                int count;

                /**
                 * @brief Name of the image to be downloaded.
                 */
                QString image_to_download;

                /**
                 * @brief ImageOutputController Constructor.
                 * @param parent To be used by Qt.
                 */
                explicit ImageOutputController(QObject* parent = nullptr);

                /**
                 * @brief Get image I uri.
                 * @return URI of image I.
                 */
                QString get_image_I();

                /**
                 * @brief Get image Q uri.
                 * @return URI of image Q.
                 */
                QString get_image_Q();

                /**
                 * @brief Get image R uri.
                 * @return URI of image R.
                 */
                QString get_image_R();

                /**
                 * @brief Get image B uri.
                 * @return URI of image B.
                 */
                QString get_image_B();

                /**
                 * @brief Get image N uri.
                 * @return URI of image N.
                 */
                QString get_image_N();

                /**
                 * @brief Get image N Ext uri.
                 * @return URI of image N Ext.
                 */
                QString get_image_N_ext();

                /**
                 * @brief Get image N Fix uri.
                 * @return URI of image N Fix.
                 */
                QString get_image_N_fix();

                /**
                 * @brief Get image N Tmo uri.
                 * @return URI of image N Tmo.
                 */
                QString get_image_N_tmo();

                /**
                 * @brief Get image V uri.
                 * @return URI of image V.
                 */
                QString get_image_V();

                /**
                 * @brief Get image E uri.
                 * @return URI of image E.
                 */
                QString get_image_E();

                /**
                 * @brief Get image P uri.
                 * @return URI of image P.
                 */
                QString get_image_P();

                /**
                 * @brief Store name of the image that has to be downloaded.
                 * @param imageName Name of the image.
                 */
                void set_image_to_download(QString imageName);

                /**
                 * @brief Download image.
                 * @return Nothing.
                 */
                QString download();

            signals:
                /**
                 * @brief Signal for notifying when an image has changed in backend.
                 */
                void image_changed();
        };
    }
}

#endif // IMAGEOUTPUTCONTROLLER_H
