#ifndef CUSTOMTCPSERVER_H
#define CUSTOMTCPSERVER_H

#include "mythread.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Timestamp.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;

class CustomTCPServer : public ServerApplication
{
public:
    CustomTCPServer() {}
    ~CustomTCPServer() {}
protected:
    void initialize(Application& self);
    void uninitialize();
    int main(const std::vector<std::string>& args);
    ThreadRunnable runnable[1024];
};


#endif // CUSTOMTCPSERVER_H
