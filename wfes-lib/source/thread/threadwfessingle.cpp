#include "threadwfessingle.h"

WorkerThread::WorkerThread(QObject *parent) : QThread(parent) {}

WorkerThread::~WorkerThread() {
}

void WorkerThread::run() {
}

