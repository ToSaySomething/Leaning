#include "work.h"
/*
Work == TCPServerDispatcher,派遣管理者. 接收消息变化,放入队列.管理 连接数.
当放入队列时,会激活  PooledThread 中的事件 .
PooledThread 又反过来 激活 TCPServerDispatcher::run() [姑且叫 有条件时相互激活吧 ]
*/
Worker::Worker(Poco::ThreadPool& threadpool, Params::Ptr pParams):
    _threadPool(threadpool),
    _pParams(pParams),
    _stopped(false)
{
    _curthreads = 0;
    _rc = 1;
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
    if (rc == 0)
        delete this;
}

void Worker::stop()
{
    _stopped = true;
    _queue.clear();
    _queue.wakeUpAll();
}

void Worker::run()
{
    AutoPtr<Worker> guard(this, true);

    while (true)
    {
        AutoPtr<Notification> pNf(_queue.waitDequeueNotification());
        if(pNf)
        {
            WorkNotification* pWorkNf = dynamic_cast<WorkNotification*>(pNf.get());
            if (pWorkNf)
            {
                Connection connect(pWorkNf->socket());
                connect.run();

            }
        }
        if  (_stopped || (_curthreads > 1 && _queue.empty()) )
        {//STOP or no_curthreads or no empty queue
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
        std::cout << " enqueue: " << std::endl;
        _queue.enqueueNotification(new WorkNotification(ss));
        _threadPool.start(*this);
        _curthreads++;
    }
    catch(Poco::Exception&e)
    {

    }


}
