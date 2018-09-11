
#ifndef SERVER_H
#define SERVER_H
#include "work.h"
#include "Poco/Net/ServerSocket.h"
#include "serverconntectfactory.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"

using Poco::Net::StreamSocket;
using Poco::Net::ServerSocket;
class Worker;



class  TCPServerConnectionFilter: public Poco::RefCountedObject

{
public:
    typedef Poco::AutoPtr<TCPServerConnectionFilter> Ptr;

    virtual bool accept(const StreamSocket& socket) = 0;

protected:
    virtual ~TCPServerConnectionFilter();
};


class  TCPServer: public Poco::Runnable

{
public:
    TCPServer( Poco::UInt16 portNumber = 0, Params::Ptr pParams = 0);



    TCPServer( const ServerSocket& socket, Params::Ptr pParams = 0);


    TCPServer( Poco::ThreadPool& threadPool, const ServerSocket& socket, Params::Ptr pParams = 0);


    virtual ~TCPServer();


    const Params& params() const;


    void start();


    void stop();


    int currentThreads() const;
        /// Returns the number of currently used connection threads.

    int maxThreads() const;
        /// Returns the maximum number of threads available.

    int totalConnections() const;
        /// Returns the total number of handled connections.

    int currentConnections() const;
        /// Returns the number of currently handled connections.

    int maxConcurrentConnections() const;
        /// Returns the maximum number of concurrently handled connections.

    int queuedConnections() const;


    int refusedConnections() const;


    const ServerSocket& socket() const;


    Poco::UInt16 port() const;


    void setConnectionFilter(const TCPServerConnectionFilter::Ptr& pFilter);


    TCPServerConnectionFilter::Ptr getConnectionFilter() const;


protected:
    void run();
    static std::string threadName(const ServerSocket& socket);
        /// Returns a thread name for the server thread.

private:

    ServerSocket _socket;
    Worker* _worker;
    TCPServerConnectionFilter::Ptr _pConnectionFilter;
    Poco::Thread _thread;
    bool _stopped;
};


//
// inlines
//
inline const ServerSocket& TCPServer::socket() const
{
    return _socket;
}


inline Poco::UInt16 TCPServer::port() const
{
    return _socket.address().port();
}


inline TCPServerConnectionFilter::Ptr TCPServer::getConnectionFilter() const
{
    return _pConnectionFilter;
}





#endif // SERVER_H
