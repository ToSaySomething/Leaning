#include "config.h"
#include "customtcpserver.h"
#include "customtcpconnectionfactory.h"
#include "Poco/Timestamp.h"

void CustomTCPServer::initialize(Poco::Util::Application &self){
    ServerApplication::loadConfiguration();
    ServerApplication::initialize(self);
}

void CustomTCPServer::uninitialize(){
    ServerApplication::uninitialize();
}

int CustomTCPServer::main(const std::vector<std::string> &args){
    unsigned short port = (unsigned short) config().getInt("CustomTCPServer.port", ServerPort);
    //bind
    Poco::Net::ServerSocket serverScoket(port);
    //pass
    Poco::Net::TCPServer server(new CustomTCPConnectionFactory(), serverScoket);
    //start
    server.start();
    //wait
    waitForTerminationRequest();
    //stop
    server.stop();

    return Application::EXIT_OK;

}
