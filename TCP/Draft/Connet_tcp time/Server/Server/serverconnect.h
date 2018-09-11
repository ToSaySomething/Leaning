#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H

#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Exception.h"
#include "Poco/ErrorHandler.h"

using Poco::Exception;
using Poco::ErrorHandler;
using Poco::Net::StreamSocket;

class  ServerConnection: public Poco::Runnable

{
public:
    ServerConnection(const StreamSocket& socket);
    virtual ~ServerConnection();

    StreamSocket& socket();
    void start();


private:

    StreamSocket _socket;

    friend class Worker;
};

// inlines
inline StreamSocket& ServerConnection::socket()
{
    return _socket;
}


#endif // SERVERCONNECT_H
