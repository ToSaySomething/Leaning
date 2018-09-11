//TCPConnectionFactory.h

#ifndef TCPCONNECTIONFACTORY_H
#define TCPCONNECTIONFACTORY_H

#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include "tcpconnection.h"
#include <string>

using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;


class TCPConnectionFactory : public TCPServerConnectionFactory
{
public:
    TCPConnectionFactory(const std::string arg1, int arg2, double arg3):
        _arg1(arg1), _arg2(arg2), _arg3(arg3)
    {

    }
    TCPServerConnection* createConnection(const StreamSocket& socket)
    {
        return new TCPConnection(socket, _arg1, _arg2, _arg3);
    }
private:
    std::string _arg1;
    int _arg2;
    double _arg3;
};

#endif // TCPCONNECTIONFACTORY_H
