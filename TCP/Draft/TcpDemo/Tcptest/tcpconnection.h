//TCPConnection.h
#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string>

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class TCPConnection: public TCPServerConnection
{
public:
    TCPConnection(const StreamSocket& s,
                  const std::string& arg1,
                  int arg2,
                  double arg3);//参数
    void run();
private:
    std::string _arg1;
    int _arg2;
    double _arg3;
};

#endif // TCPCONNECTION_H
