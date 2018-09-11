#ifndef _QTHREAD_H
#define _QTHREAD_H

#include <QThread>
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
private:
    int m_runCount;
};



#endif // _QTHREAD_H
