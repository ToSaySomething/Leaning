#ifndef _QTHREAD_H
#define _QTHREAD_H
#include <QThread>
#include <iostream>
class _Thread : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);

public:
    _Thread(QObject* par);
    ~_Thread();
    void setRunCount(int count);
    void run();
    void doSomething();
    void Something();
private:
    int m_runCount;
    bool flag;
};



#endif // _QTHREAD_H
