//TCPServer.cpp

#include "tcpserver.h"
#include "tcpconnection.h"
#include "tcpconnectionfactory.h"

void TCPServer::initialize(Application& self)
{
    ServerApplication::loadConfiguration();
    ServerApplication::initialize(self);
}

void TCPServer::uninitialize()
{
    ServerApplication::uninitialize();
}

int TCPServer::main(const std::vector<std::string>& args)
{
    //回头来说PoechantTCPServer::main(const std::vector<std::string>& args)，
    //其过程就是创建一个绑定了地址的ServerSocket，
    //把它传给TCPServer，当然别忘了把工程对象也给你的TCPServer传一个。
    //最后就start()，waitForTerminationRequest和stop()就行了。
    unsigned short port = (unsigned short) config().getInt("TCPServer.port",12346);
    std::string format(config().getString("TCPServer.format",DateTimeFormat::ISO8601_FORMAT));

    // 1. Bind a ServerSocket with an address
    ServerSocket serverSocket(port);

    // 2. Pass the ServerSocket to a TCPServer
    Poco::Net::TCPServer server(new PoechantTCPConnectionFactory(format), serverSocket);

    // 3. Start the TCPServer
    server.start();

    // 4. Wait for termination
    waitForTerminationRequest();

    // 5. Stop the TCPServer
    server.stop();

    return Application::EXIT_OK;
}
