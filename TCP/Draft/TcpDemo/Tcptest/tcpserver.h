//TCPServer.h
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;

class TCPServer: public ServerApplication
{
public:
    TCPServer(){}
    ~TCPServer(){}
protected:
    void initialize(Application& self);
    void uninitialize();
    int main(const std::vector<std::string> &args);
};

#endif // TCPSERVER_H
