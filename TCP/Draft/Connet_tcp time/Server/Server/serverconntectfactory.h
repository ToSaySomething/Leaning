#ifndef SERVERCONNTECTFACTORY_H
#define SERVERCONNTECTFACTORY_H



#include "serverconnect.h"
#include "Poco/SharedPtr.h"


class  ServerConnectionFactory

{
public:
    typedef Poco::SharedPtr<ServerConnectionFactory> Ptr;
    ServerConnectionFactory();

    virtual ~ServerConnectionFactory();
    virtual ServerConnection* createConnection(const StreamSocket& socket) = 0;
};


template <class S>
class ServerConnectionFactoryImpl: public ServerConnectionFactory
    //implementation
{
public:
    ServerConnectionFactoryImpl()
    {
    }

    ~ServerConnectionFactoryImpl()
    {
    }

    ServerConnection* createConnection(const StreamSocket& socket)
    {
        return new S(socket);
    }
};


#endif // SERVERCONNTECTFACTORY_H
