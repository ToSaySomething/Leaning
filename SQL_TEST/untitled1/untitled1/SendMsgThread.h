#ifndef SENDMSGTHREAD_H
#define SENDMSGTHREAD_H

#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"

using Poco::Runnable;
using Poco::NotificationQueue;
using std::string;

class SendMsgThread:public Runnable{
private:
    NotificationQueue& queue;
    void deal(string, int);

public:
    SendMsgThread(NotificationQueue&);
    virtual void run();
};

#endif // SENDMSGTHREAD_H
