#include "activity.h"

using Poco::Net::ServerSocket;


MyActivity::MyActivity(const ServerSocket& so, Poco::ThreadPool& threadpool, Params::Ptr pParams):
    //_activity(this, &MyActivity::runActivity),
    _socket(so),
    _worker(new Worker(threadpool, pParams)),
    //_thread(threadName(_socket)),
    _stopped(true)

{
    Poco::ThreadPool& pool = Poco::ThreadPool::defaultPool();
    if (pParams)
    {//add
        int toAdd = pParams->getMaxThreads() - pool.capacity();
        if (toAdd > 0) pool.addCapacity(toAdd);
    }
    _worker = new Worker(pool, pParams);
}



void MyActivity::start()
{
    poco_assert (_stopped);
    _stopped = false;
    _thread.start(*this);
}

void MyActivity::stop()
{
    if (!_stopped)
    {
        _stopped = true;
        _thread.join();
        _worker->stop();
    }
}


void MyActivity::run()
{

    while(!_stopped)
    {
        std::cout << " --- activity: " << std::endl;
        Poco::Timespan timeout(TIME);
        try
        {
            bool flag = _socket.poll(timeout, Poco::Net::Socket::SELECT_READ);
            if (flag)
            {
                try
                {
                    StreamSocket ss = _socket.acceptConnection();
                    if (!_pConnectionFilter || _pConnectionFilter->accept(ss))
                    {
                          ss.setNoDelay(true);
                          _worker->enqueue(ss);
                    }
                }
                catch (Poco::Exception& exc)
                {
                    std::cout<< " Exception"<< exc.what() << std::endl;
                }
            }
            std::cout << " --- end activity : " << std::endl << std::endl;
        }
        catch(Poco::Exception& e)
        {
            std::cout<< " Exception"<< e.what() << std::endl;
            Thread::sleep(50);
        }
    }
}


const Params& MyActivity::params()
{
    return _worker->params();
}

void MyActivity::initpoll()
{
    //Worker worke1(queue);
    //ThreadPool::defaultPool().start(worke1);
    //ThreadPool::defaultPool().start(worke1);
//    for(int i=0; i<3; i++)
//    {
//        Worker worke1(queue);
//        ThreadPool::defaultPool().start(worke1);
//    }

}

/*
#include "activity.h"
#include "thread.h"

using Poco::Net::ServerSocket;


MyActivity::MyActivity(const ServerSocket& so):
    _activity(this, &MyActivity::runActivity),
    _socket(so)
{
//    memset(vis, 0, sizeof(vis));
}

void MyActivity::start()
{
    _activity.start();
}

void MyActivity::stop()
{
    _activity.stop();
    _activity.wait();
}

void MyActivity::runActivity()
{

    while(!_activity.isStopped())
    {
        std::cout << "Server : Activity find is running: " << std::endl;

        //if client
        try
        {
            if( _socket.poll(Poco::Timespan(TIME,0), Poco::Net::Socket::SelectMode::SELECT_READ))
            {
                Poco::Net::StreamSocket ss = _socket.acceptConnection();
                ss.setNoDelay(true);

                runnable._queue.push(ss);
                pool.addCapacity(1);
                pool.start(runnable);
                std::cout << "thread" << std::endl;
             }
        }
        catch(Poco::ExistsException& e)
        {
            std::cout << "Server : error: "<< e.what() << std::endl;
        }

    }
}
*/

/*
//if client
try
{
    if( _socket.poll(Poco::Timespan(TIME,0), Poco::Net::Socket::SelectMode::SELECT_READ))
    {
        Poco::Net::StreamSocket ss = _socket.acceptConnection();
        ss.setNoDelay(true);

        runnable._queue.push(ss);

        Poco::ThreadPool::defaultPool().start(runnable);
        std::cout << "thread" << std::endl;
        //Poco::Util::ServerApplication::aitForTerminationRequest();

     }
}
catch(Poco::ExistsException& e)
{
    std::cout << "Server : error: "<< e.what() << std::endl;
}
*/

/*

                ThreadRunnable runnable[1024];
                for(int i=0; i<MAX_THREAD; i++)
                {
                    if(!vis[i])
                    {
                        while(_queue.empty())
                        {
                            _queue.front();
                        }
                        Poco::ThreadPool::defaultPool().start(runnable[i]);

                        vis[i] = 1;
                    }
                }
*/


