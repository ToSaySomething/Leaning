#include "_qthread.h"
#include <QDebug>
#include <iostream>
_Thread::_Thread(QObject* par) :
    QThread(par),
    m_runCount(20)
{

}

_Thread::~_Thread()
{
    qDebug() << "~Thread";
}



void _Thread::setRunCount(int count)
{
    m_runCount = count;
}

void _Thread::run()
{
    int count = 0;

    while(1)
    {
        sleep(1);
        ++count;
        doSomething();
        if(m_runCount == count)
        {
            break;
        }
    }
}

void _Thread::doSomething()
{
    std::cout << "ss" << std::endl;
}
