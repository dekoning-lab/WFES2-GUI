#include "masterController.h"

namespace wfes {
    namespace controllers {
        MasterController::MasterController(QObject* parent)
        : QObject(parent)
        {
        }

        QString MasterController::execute()
        {

            qDebug() << "Inside execute!";
            wfes_single single = wfes_single();
            single.execute();
            return QString();
        }
    }
}
