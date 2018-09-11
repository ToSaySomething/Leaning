#include "activity.h"

using Poco::Net::ServerSocket;


MyActivity::MyActivity(const ServerSocket& so):
    _activity(this, &MyActivity::runActivity),
    _socket(so)
{

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

    Worker worke1(queue);
    Worker worke2(queue);
    ThreadPool::defaultPool().start(worke1);
    ThreadPool::defaultPool().start(worke1);

    while(!_activity.isStopped())
    {
        std::cout << "activity: " << std::endl;
        Poco::Timespan timeout(TIME);
        bool flag = _socket.poll(timeout, Poco::Net::Socket::SELECT_READ);
        if (flag)
        {
            try
            {
                 std::cout << "StreamSocket: " << std::endl;
                 StreamSocket ss = _socket.acceptConnection();
                 ss.setNoDelay(true);
                 queue.enqueueNotification(new WorkNotification(ss));

            }
            catch(Poco::Exception& e)
            {
                std::cout<< " Exception"<< e.what() << std::endl;
            }

        }

        Thread::sleep(2000);
        std::cout << "activity: " << std::endl;
    }
    //stop thread
    while(!queue.empty()) {
        Poco::Thread::sleep(100);
    }
    queue.wakeUpAll();
    ThreadPool::defaultPool().joinAll();
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


