#include "wfesLib.h"

WfesLib::WfesLib(QObject *parent) : QObject(parent){}

WfesLib::~WfesLib(){}

void WfesLib::execute(){
    //qDebug() << "Inside execute!";
    wfes_single single = wfes_single();
    single.execute();

}
