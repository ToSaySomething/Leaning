#ifndef SERVERCONNECTIONFACTORY_H
#define SERVERCONNECTIONFACTORY_H
#include "ServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class ServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory
{
public:
    TCPServerConnection* createConnection(const StreamSocket &socket);
};
#endif // SERVERCONNECTIONFACTORY_H
