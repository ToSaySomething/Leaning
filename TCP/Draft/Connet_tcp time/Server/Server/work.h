#ifndef WORK_H
#define WORK_H

#include "worknotification.h"
#include "params.h"
#include "connect.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadPool.h"

using Poco::Runnable;
using Poco::AutoPtr;


class Worker: public Runnable
{
    const long long LEN = 1024;
    const long long TIME = 200000;
public:
    Worker(Poco::ThreadPool& threadpool,Params::Ptr pParams);
    ~Worker();
    void run();

public:
    void duplicate();
    void release();//deletes
    void stop();
    void rece();
    void send();
    void enqueue(const StreamSocket& ss);
    void beginConnection();
    void endConnection();
    const Params& params() ;
private:

    NotificationQueue _queue;
    StreamSocket _socket;
    mutable Poco::FastMutex _mutex;
    Poco::ThreadPool& _threadPool;
    Params::Ptr _pParams;

    int _rc;
    int _curthreads;
    int  _totalConnections;
    int  _currentConnections;
    int  _maxConcurrentConnections;
    int  _refusedConnections;
    bool _stopped;

};



#endif // WORK_H
