#ifndef WORK_H
#define WORK_H


#include "worknotification.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"
#include <iostream>
using Poco::Runnable;
using Poco::AutoPtr;


class Worker: public Runnable
{
    const long long LEN = 1024;
public:
    Worker(NotificationQueue& q): _queue(q)
    {}
    void run();

public:
    void rece(StreamSocket socket);
    void send(StreamSocket socket);


private:
    NotificationQueue& _queue;
};


#endif // WORK_H
