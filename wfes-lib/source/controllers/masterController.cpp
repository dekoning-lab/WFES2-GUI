#include "masterController.h"

namespace wfes {
namespace controllers {

QString MasterController::getResults() const
{
    qDebug() << this->results->pExt;
    boost::format fmt = boost::format(DPF) % (this->results->pExt);

    if(isnan(this->results->pExt))
        return "";
    else
        return QString::fromStdString(fmt.str());
}

MasterController::MasterController(QObject* parent)
        : QObject(parent)
        {
        }

        QString MasterController::execute()
        {

            qDebug() << "Inside execute!";
            wfes_single single = wfes_single();
            results = single.execute();

            qDebug("P_ext = " DPF "\n", results->pExt);

            qDebug("P_fix = " DPF, results->pFix);
            qDebug("T_abs = " DPF, results->tAbs);
            qDebug("T_abs_std = " DPF, results->tAbsStd);
            qDebug("T_ext = " DPF, results->tExt);
            qDebug("T_ext_std = " DPF , results->tExtStd);
            qDebug("N_ext = " DPF, results->nExt);
            qDebug("T_fix = " DPF, results->tFix);
            qDebug("T_fix_std = " DPF, results->tFixStd);

            emit resultsChanged();

            return QString();
        }
    }
}
