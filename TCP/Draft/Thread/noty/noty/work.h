#ifndef WORK_H
#define WORK_H
#include "worknotification.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"
using Poco::Runnable;
using Poco::AutoPtr;

class Worker: public Runnable
{
public:
    Worker(NotificationQueue& queue): _queue(queue) {}
    void run();
private:
    NotificationQueue& _queue;
};

#endif // WORK_H
