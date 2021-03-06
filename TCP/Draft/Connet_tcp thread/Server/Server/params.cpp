#include "params.h"

Params::Params():
    _threadIdleTime(10000000),
    _threadPriority(Poco::Thread::PRIO_NORMAL),
    _maxThreads(0),
    _maxQueued(64)

{
}

Params::~Params()
{}

void Params::setThreadIdleTime(const Poco::Timespan& milliseconds)
{
    _threadIdleTime = milliseconds;
}

void Params::setThreadPriority(Poco::Thread::Priority prio)
{
    _threadPriority = prio;
}



void Params::setMaxThreads(int count)
{
    poco_assert (count > 0);

    _maxThreads = count;
}


void Params::setMaxQueued(int count)
{
    poco_assert (count >= 0);

    _maxQueued = count;
}



