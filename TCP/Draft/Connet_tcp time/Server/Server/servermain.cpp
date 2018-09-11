#include "servermain.h"
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




    Poco::Net::ServerSocket serverScoket ( 9000 );
    //timeout
    Poco::Timespan timeout( 1000, 0 );
    serverScoket.setReceiveTimeout( timeout );

    Params::Ptr params = new Params;
    params->setMaxQueued( 10 );//设定队列的最大长度
    params->setMaxThreads( 10 );//设定　TcpServer 最大线程的个数

    ThreadPool threadpool(7,7,7);

    MyActivity server(serverScoket, threadpool, params );//a thread
    //TCPServer server(serverScoket, params);
    server.start();
    waitForTerminationRequest();
    server.stop();

    return Application::EXIT_OK;

}
