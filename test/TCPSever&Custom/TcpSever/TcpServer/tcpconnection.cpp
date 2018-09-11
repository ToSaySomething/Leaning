#include "tcpconnection.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"
#include <iostream>
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/URI.h"
#include "Poco/StreamCopier.h"


TCPConnection1::TCPConnection1(const StreamSocket& s):
    TCPServerConnection(s)
{
}

void TCPConnection1::run()
{
    Poco::Util::Application& app = Poco::Util::Application::instance();
    // 日志输出连接的TCP用户的地址（IP和端口）
    app.logger().information( "Request from " + this->socket().peerAddress().toString() );
    try
    {
        std::string dt(" Sucessful connect , from : Server \n data:");

        //while connect
        char str[1024] = {0};
        int len = 1024;
        int num = socket().receiveBytes( str, len );
        dt.append(str);
        while( num > 0){
            if( num > 0 ){
                socket().sendBytes(dt.data(), (int) dt.length());
                //app.logger().information("Server: Sucessful receive:");
                std::cout<< "Server: Sucessful receive: " << str << " from client "<<std::endl;
            }
            num = socket().receiveBytes( str, len );
        }
        app.logger().information("Server: the connection closed.");

    }
    catch (Poco::Exception& e)
    {
        app.logger().log(e);
    }
}
