#ifndef CUSTOMTCPCONNECTION_H
#define CUSTOMTCPCONNECTION_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>

using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

class CustomTCPConnection: public TCPServerConnection
{
public:
    CustomTCPConnection(const StreamSocket& s);
    void run();
};

#endif // CUSTOMTCPCONNECTION_H
