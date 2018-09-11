#include "customtcpconnection.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"
#include "people.pb.h"
#include "people.pb.cc"
#include <iostream>

CustomTCPConnection::CustomTCPConnection(const StreamSocket& s):
    TCPServerConnection(s)
{
}

void CustomTCPConnection::run()
{
    Poco::Util::Application& app = Poco::Util::Application::instance();
    // 日志输出连接的TCP用户的地址（IP和端口）
    app.logger().information( "Request from " + this->socket().peerAddress().toString() );
    try
    {
        std::string dt(" Sucessful connect , from : Server \n data:");

        //while connect
        char str[1024] = {"\0"};
        int len = 1024;
        int num = socket().receiveBytes( str, len );
        dt.append(str);
        str[strlen(str)] = '\0';
        while( num > 0)
        {
            if( num > 0 )
            {
                std::cout<< "Server: Sucessful receive: " << str << " from client "<<std::endl;
                std::string  data;
                people::People p;
                p.set_name("Hideto");
                p.set_id("131232");
                p.set_email("hideto.bj@gmail.com");
                p.SerializeToString(&data);

                socket().sendBytes(data.data(), (int) data.length());

                //socket().sendBytes(dt.data(), (int) dt.length());
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

//else {
//send(connectfd, "Fucking client!\n", 16, 0);
//std::string  data = "Fucking client!\n";
//socket().sendBytes(data.data(), (int) data.length());
//}

