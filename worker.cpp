#include "worker.h"

#include <QDebug>

Worker::Worker(QObject *parent) : QObject(parent)
{

}

Worker::~Worker()
{
    qDebug() << Q_FUNC_INFO;
}

void Worker::doWork(const QString &parameter) {
    QString result("hello");

    // 여기서 오래걸리는 작업을 수행

    emit resultReady(result + parameter);
}
