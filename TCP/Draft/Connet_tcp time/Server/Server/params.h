#ifndef PARAMS_H
#define PARAMS_H

#include "Poco/RefCountedObject.h"
#include "Poco/Timespan.h"
#include "Poco/Thread.h"
#include "Poco/AutoPtr.h"

class  Params: public Poco::RefCountedObject
{

public:
    typedef Poco::AutoPtr<Params> Ptr;
    Params();
    ~Params();

public:
    void setThreadIdleTime(const Poco::Timespan& idleTime);
    void setMaxQueued(int count);
    int getMaxQueued();
    void setMaxThreads(int count);
    int getMaxThreads();

    const Poco::Timespan& getThreadIdleTime();
    void setThreadPriority(Poco::Thread::Priority prio);
    Poco::Thread::Priority getThreadPriority();

private:

    Poco::Timespan _threadIdleTime;
    Poco::Thread::Priority _threadPriority;
    int _maxThreads;
    int _maxQueued;


};


inline const Poco::Timespan& Params::getThreadIdleTime()
{
    return _threadIdleTime;
}

inline int Params::getMaxThreads()
{
    return _maxThreads;
}

inline int Params::getMaxQueued()
{
    return _maxQueued;
}

inline Poco::Thread::Priority Params::getThreadPriority()
{
    return _threadPriority;
}

#endif // PARAMS_H
