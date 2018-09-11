#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "work.h"
#include "Poco/Net/ServerSocket.h"

#include "Poco/Net/SocketStream.h"
#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"


using Poco::Thread;
using Poco::ThreadPool;
using Poco::Net::ServerSocket;


class MyActivity
{

    static const long TIME = 2000000;
    static const int Port = 9000;
    static const int MAX_THREAD = 1024;
public:
    MyActivity(const ServerSocket&);
    ~MyActivity(){}

public:
    void start();
    void stop();
protected:
    void runActivity();

private:
    Poco::Activity<MyActivity> _activity;
    ServerSocket _socket;
    Poco::NotificationQueue queue;
};



#endif // ACTIVITY_H
