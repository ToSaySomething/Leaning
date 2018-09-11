#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include <iostream>
class ThreadRunnable : public Poco::Runnable
{
    void run();
};

#endif // MYTHREAD_H
