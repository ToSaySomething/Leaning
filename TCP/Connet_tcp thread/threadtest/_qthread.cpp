#include "_qthread.h"
#include <QDebug>
#include <iostream>

_Thread::_Thread(QObject* par) :
    QThread(par),
    m_runCount(100)
{
    flag = true;
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

    std::cout<<"s\n";
}

void _Thread::Something()
{
    if(flag) flag = false;
    else{
        flag = true;
        std::cout<<"eeee\n";
    }
}




