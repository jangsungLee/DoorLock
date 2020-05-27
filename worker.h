#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker(void (*_fp)() = nullptr);
    ~Worker() override;

protected:
    void run() override;

private:
    void (*fp)();

};

#endif // WORKER_H
