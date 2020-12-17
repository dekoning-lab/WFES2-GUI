#ifndef SYSTEMOPERATIONS_H
#define SYSTEMOPERATIONS_H

#include <QDesktopServices>
#include <QDebug>
#include <QObject>
#include <QUrl>

#include <wfes-lib_global.h>

namespace wfes {
    namespace controllers {

        class WFESLIBSHARED_EXPORT SystemOperations : public QObject {
            Q_OBJECT

            public:
                SystemOperations() = default;

                Q_INVOKABLE void openUrlInFileExplorer(QString path) {
                    path = "file://" + path;
                    QDesktopServices::openUrl(QUrl(path));
                    qDebug() << path;
                }

        };
    }
}
#endif // SYSTEMOPERATIONS_H
