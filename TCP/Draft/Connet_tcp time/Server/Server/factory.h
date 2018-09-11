#ifndef FACTORY_H
#define FACTORY_H
#include "connect.h"
#include "serverconntectfactory.h"
#include "Poco/Net/StreamSocket.h"


using Poco::Net::StreamSocket;

class MyConnectionFactory: public ServerConnectionFactory
{
public:
    ServerConnection* createConnection(const StreamSocket& socket);
};

/*
class  MyConnectionFactory

{
public:
    typedef Poco::SharedPtr<MyConnectionFactory> Ptr;
    virtual ~MyConnectionFactory();
    virtual MyConnection* createConnection(const StreamSocket& socket) = 0;

protected:
    MyConnectionFactory();

private:
    MyConnectionFactory(const MyConnectionFactory&);
    MyConnectionFactory& operator = (const MyConnectionFactory&);
};


template <class S>
class MyConnectionFactoryImpl: public MyConnectionFactory
    //  implementation
{
public:
    MyConnectionFactoryImpl()
    {
    }

    ~MyConnectionFactoryImpl()
    {
    }

    MyConnection* createConnection(const StreamSocket& socket)
    {
        return new S(socket);
    }
};*/

#endif // FACTORY_H
