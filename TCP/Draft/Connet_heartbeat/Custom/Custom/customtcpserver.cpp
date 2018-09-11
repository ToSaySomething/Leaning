#include "config.h"
#include "customtcpserver.h"
#include "customtcpconnectionfactory.h"
#include "Poco/Timestamp.h"


void CustomTCPServer::initialize(Poco::Util::Application &self)
{
    ServerApplication::loadConfiguration();
    ServerApplication::initialize(self);
}

void CustomTCPServer::uninitialize()
{
    ServerApplication::uninitialize();
}

int CustomTCPServer::main(const std::vector<std::string> &args)
{

    int Port = ServerPort;
    unsigned short port = (unsigned short) config().getInt("CustomTCPServer.port", Port);

    //bind
    Poco::Net::ServerSocket serverScoket(port);
    //timeout
    Poco::Timespan timeout( 1000, 0 );
    serverScoket.setReceiveTimeout( timeout );
    //queue
    Poco::Net::TCPServerParams::Ptr param = new Poco::Net::TCPServerParams;
    param->setMaxQueued( 10 );//设定队列的最大长度
    param->setMaxThreads( 10 );//设定　TcpServer 最大线程的个数
    //pass
    Poco::Net::TCPServer server(new CustomTCPConnectionFactory(), serverScoket, param);
    //start

    server.start();
    //wait
    waitForTerminationRequest();
    //stop
    server.stop();

    return Application::EXIT_OK;

}
