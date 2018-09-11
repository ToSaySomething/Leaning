#ifndef CUSTOMTCPCONNECTIONFACTORY_H
#define CUSTOMTCPCONNECTIONFACTORY_H

#include "customtcpconnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class CustomTCPConnectionFactory: public Poco::Net::TCPServerConnectionFactory
{
public:
    TCPServerConnection* createConnection(const StreamSocket& socket);
};
#endif // CUSTOMTCPCONNECTIONFACTORY_H
