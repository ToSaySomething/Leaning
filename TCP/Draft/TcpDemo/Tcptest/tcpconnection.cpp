//TCPConnection.cpp

#include "tcpconnection.h"
#include "Poco/Util/Application.h"
#include "Poco/Timestamp.h"
#include "Poco/Exception.h"
#include "Poco/DateTimeFormatter.h"





TCPConnection::TCPConnection(const StreamSocket& s, const std::string& arg1, int arg2, double arg3):
    TCPServerConnection(s), _arg1(arg1), _arg2(arg2), _arg3(arg3)
{

}



void TCPConnection::run()
{
    Poco::Util::Application& app =  Poco::Util::Application::instance();
    app.logger().information("Request from" + this->socket().peerAddress().toString() );
    try
    {
        Poco::Timestamp now;
        std::string dt( "hello word , from : CustomTCPConnection" );//Poco::DateTimeFormatter::format(now, _format)
        dt.append("\r\n");
        socket().sendBytes(dt.data(), (int)dt.length());
    }
    catch(Poco::Exception& e)
    {
        app.logger().log(e);
    }
}
