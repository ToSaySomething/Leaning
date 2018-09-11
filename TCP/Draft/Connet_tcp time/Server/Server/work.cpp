#include "work.h"

Worker::Worker( Poco::ThreadPool& threadpool, Params::Ptr pParams):
    _threadPool(threadpool),
    _pParams(pParams),
    _rc(1),
    _curthreads(0),
    _totalConnections(0),
    _currentConnections(0),
    _maxConcurrentConnections(0),
    _refusedConnections(0),
    _stopped(false)

{

}

Worker::~Worker()
{}

void Worker::stop()
{
    _stopped = true;
    _queue.clear();
    _queue.wakeUpAll();
}

void Worker::duplicate()
{
    _mutex.lock();
    ++_rc;
    _mutex.unlock();
}


void Worker::release()
{
    _mutex.lock();
    int rc = --_rc;
    _mutex.unlock();
    if (rc == 0) delete this;
}

void Worker::run()
{
    AutoPtr<Worker> guard(this, true); // ensure object stays alive
    while (true)
    {
        AutoPtr<Notification> pNf(_queue.waitDequeueNotification());
        if (pNf)
        {
            WorkNotification* pCNf = dynamic_cast<WorkNotification*>(pNf.get());
            if(pCNf)
            {
                Connection connect(pCNf->socket());
                connect.run();
            }

        }

        Poco::FastMutex::ScopedLock lock(_mutex);
        if (_stopped || (_curthreads > 1 && _queue.empty()))
        {
            --_curthreads;
            break;
        }
    }
}

void Worker::enqueue(const StreamSocket& ss)
{
    Poco::FastMutex::ScopedLock lock(_mutex);
    try
    {
        std::cout<<"enqueue****"<<std::endl;
        _queue.enqueueNotification(new WorkNotification(ss));
        _threadPool.start(*this);
        _curthreads++;
    }
    catch(Poco::Exception&e)
    {

    }


}

void Worker::beginConnection()
{
    Poco::FastMutex::ScopedLock lock(_mutex);

    ++_totalConnections;
    ++_currentConnections;
    if (_currentConnections > _maxConcurrentConnections)
        _maxConcurrentConnections = _currentConnections;
}


void Worker::endConnection()
{
   Poco::FastMutex::ScopedLock lock(_mutex);

    --_currentConnections;
}


void Worker::rece()
{
    char buff[LEN]={0};
    int len = _socket.receiveBytes(buff, LEN);
    if(len <= 0)
    {
        std::cout << "len<= 0" << std::endl;
    }
    else
    {
        std::cout << "Server: receive "<< buff<<" " << _socket.peerAddress() << std::endl;
    }
}

void Worker::send()
{
    char buff1[LEN] = "receive from server";
    _socket.sendBytes(buff1, LEN);
}

const Params& Worker::params()
{
    return *_pParams;
}
