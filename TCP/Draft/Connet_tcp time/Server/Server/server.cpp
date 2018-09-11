

#include "server.h"
#include "Poco/ErrorHandler.h"


using Poco::ErrorHandler;



TCPServerConnectionFilter::~TCPServerConnectionFilter()
{
}

TCPServer::TCPServer( Poco::UInt16 portNumber, Params::Ptr pParams):
    _socket(ServerSocket(portNumber)),
    _thread(threadName(_socket)),
    _stopped(true)
{
    Poco::ThreadPool& pool = Poco::ThreadPool::defaultPool();
    if (pParams)
    {
        int toAdd = pParams->getMaxThreads() - pool.capacity();
        if (toAdd > 0) pool.addCapacity(toAdd);
    }
    _worker = new Worker(pool, pParams);
}


TCPServer::TCPServer( const ServerSocket& socket, Params::Ptr pParams):
    _socket(socket),
    _thread(threadName(socket)),
    _stopped(true)
{
    Poco::ThreadPool& pool = Poco::ThreadPool::defaultPool();
    if (pParams)
    {
        int toAdd = pParams->getMaxThreads() - pool.capacity();
        if (toAdd > 0) pool.addCapacity(toAdd);
    }
    _worker = new Worker( pool, pParams);
}


TCPServer::TCPServer( Poco::ThreadPool& threadPool, const ServerSocket& socket, Params::Ptr pParams):
    _socket(socket),
    _worker(new Worker(threadPool, pParams)),
    _thread(threadName(socket)),
    _stopped(true)
{
}


TCPServer::~TCPServer()
{
    try
    {
        stop();
        _worker->release();
    }
    catch (...)
    {
        poco_unexpected();
    }
}


const Params& TCPServer::params() const
{
    return _worker->params();
}


void TCPServer::start()
{
    poco_assert (_stopped);

    _stopped = false;
    _thread.start(*this);
}


void TCPServer::stop()
{
    if (!_stopped)
    {
        _stopped = true;
        _thread.join();
        _worker->stop();
    }
}


void TCPServer::run()
{
    while (!_stopped)
    {
        Poco::Timespan timeout(250000);
        try
        {
            if (_socket.poll(timeout, Socket::SELECT_READ))
            {
                try
                {
                    StreamSocket ss = _socket.acceptConnection();

                    if (!_pConnectionFilter || _pConnectionFilter->accept(ss))
                    {
                        // enable nodelay per default: OSX really needs that
//#if defined(POCO_OS_FAMILY_UNIX)
                        //if (ss.address().family() != AddressFamily::UNIX_LOCAL)
//#endif
                        //{
                            ss.setNoDelay(true);
                        //}
                        _worker->enqueue(ss);
                    }
                }
                catch (Poco::Exception& exc)
                {
                    ErrorHandler::handle(exc);
                }
                catch (std::exception& exc)
                {
                    ErrorHandler::handle(exc);
                }
                catch (...)
                {
                    ErrorHandler::handle();
                }
            }
        }
        catch (Poco::Exception& exc)
        {
            ErrorHandler::handle(exc);
            // possibly a resource issue since poll() failed;
            // give some time to recover before trying again
            Poco::Thread::sleep(50);
        }
    }
}
/*

int TCPServer::currentThreads() const
{
    return _worker->currentThreads();
}


int TCPServer::maxThreads() const
{
    return _worker->maxThreads();
}


int TCPServer::totalConnections() const
{
    return _worker->totalConnections();
}


int TCPServer::currentConnections() const
{
    return _worker->currentConnections();
}


int TCPServer::maxConcurrentConnections() const
{
    return _worker->maxConcurrentConnections();
}


int TCPServer::queuedConnections() const
{
    return _worker->queuedConnections();
}


int TCPServer::refusedConnections() const
{
    return _worker->refusedConnections();
}

*/
void TCPServer::setConnectionFilter(const TCPServerConnectionFilter::Ptr& pConnectionFilter)
{
    poco_assert (_stopped);

    _pConnectionFilter = pConnectionFilter;
}


std::string TCPServer::threadName(const ServerSocket& socket)
{
#if _WIN32_WCE == 0x0800
    // Workaround for WEC2013: only the first call to getsockname()
    // succeeds. To mitigate the impact of this bug, do not call
    // socket.address(), which calls getsockname(), here.
    std::string name("TCPServer");
    #pragma message("Using WEC2013 getsockname() workaround in TCPServer::threadName(). Remove when no longer needed.")
#else
    std::string name("TCPServer: ");
    name.append(socket.address().toString());
#endif
    return name;
}







