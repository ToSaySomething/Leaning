#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Logger.h"


using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;
using std::string;

class ServerConnection : public TCPServerConnection{
public:
    ServerConnection(const StreamSocket& s): TCPServerConnection(s){}
    void run();
    string myDeal(string, int);
};

#endif // SERVER_H
