#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "work.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include <iostream>

using Poco::Thread;
using Poco::ThreadPool;
using Poco::Net::ServerSocket;

class  MyConnectionFilter: public Poco::RefCountedObject

{
public:
    typedef Poco::AutoPtr<MyConnectionFilter> Ptr;
    virtual bool accept(const StreamSocket& socket) = 0;

protected:
    virtual ~MyConnectionFilter();
};

class MyActivity : public Poco::Runnable
{

    static const long TIME = 2000000;
    static const int Port = 9000;
    static const int MAX_THREAD = 1024;
public:
    MyActivity(const ServerSocket&, Poco::ThreadPool&, Params::Ptr pParams);
    ~MyActivity(){}

public:
    void run();
    void start();
    void stop();
    static std::string threadName(const ServerSocket& socket);

protected:

    void initpoll();
    void enqueue(const ThreadPool& pool, const StreamSocket& ss);
    const Params& params();

private:

//    Poco::Activity<MyActivity> _activity;
    ServerSocket _socket;
    Poco::NotificationQueue queue;
    Worker* _worker;
    MyConnectionFilter::Ptr _pConnectionFilter;
    Poco::Thread _thread;
    bool _stopped;
};



#endif // ACTIVITY_H
