#ifndef WORKER_H
#define WORKER_H


#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    virtual ~Worker();

public slots:
    void doWork(const QString &);

signals:
    void start(const QString &);
    void resultReady(const QString &result);

};

#endif // WORKER_H
