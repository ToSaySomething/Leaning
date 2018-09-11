#ifndef DBOPERTHREAD_H
#define DBOPERTHREAD_H

#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"
#include "Serialization.pb.h"

using Poco::Runnable;
using Poco::NotificationQueue;
using tutorial::CmdData;
using std::string;

class DbOperThread : public Runnable{
private:
    NotificationQueue& queue;
    string deal(CmdData);

public:
    DbOperThread(NotificationQueue&);
    virtual void run();
};

#endif // DBOPERTHREAD_H
