#include "customtcpconnection.h"
#include "Poco/Util/Application.h"
#include "Poco/Exception.h"
#include "people.pb.h"
#include "people.pb.cc"
#include <iostream>


CustomTCPConnection::CustomTCPConnection(const StreamSocket& s):
    TCPServerConnection(s), _state(ConnectionState::None),
    _socket(const_cast<StreamSocket&>(s)), _buff(new char[MAX_RECV_LEN])
{
}

CustomTCPConnection::~CustomTCPConnection()
{

}

void CustomTCPConnection::run()
{
    Poco::Util::Application& app = Poco::Util::Application::instance();
    // 日志输出连接的TCP用户的地址（IP和端口）
    app.logger().information( "Request from " + _socket.peerAddress().toString() );
    _state = CustomTCPConnection::Established;//connect
    try
    {
        while(true)
        {
            if(_state == CustomTCPConnection::Established)
            {
                if( _socket.poll(Poco::Timespan(TIME,0), Poco::Net::Socket::SelectMode::SELECT_READ) )
                {
                    onlyread();
                }
            }
            else if(_state == CustomTCPConnection::Closed)
            {
                return;
            }
        }
    }
    catch (Poco::Exception& e)
    {
        app.logger().log(e);
    }
    app.logger().information("Server: the connection closed.");

}

bool CustomTCPConnection::onlyread()//only read
{
    int len = _socket.receiveBytes(_buff, MAX_RECV_LEN);
    if(!len)
    {
        shutdown(CLIENT_CLOSE);// receive nothing
        return false;//closed socket
    }
    else
    {
        //format is ill?
        bool flag = isflag(_buff, len);
        if(!flag)
        {
            std::cout << "ill format" <<std::endl;
            shutdown(ILLED_FORMAT);
            return false;
        }
        std::cout<< "Server: Sucessful receive: " << _buff << " from client "<<std::endl;

        //send to client
        std::string data ="" ;
        data += tramessage(data);
        _socket.sendBytes(data.data(), MAX_RECV_LEN, 0);
        return true;
    }
}

std::string CustomTCPConnection::tramessage(std::string data1)
{
    people::People p;
    p.set_name("Hideto");
    p.set_id("131232");
    p.set_email("hideto.bj@gmail.com");
    p.SerializeToString(&data1);
    return data1;
}

void CustomTCPConnection::shutdown(const ShutdownReason& reason)
{
    if(_state == ClosedWait) return ;
    switch( reason )
    {
        case CLIENT_CLOSE:std::cout<< " closed client socket "<<std::endl;
            break;
        case SERVICE_CLOSE:std::cout<< " closed service socket "<<std::endl;
            break;
        case ILLED_FORMAT :std::cout<< "service :ill format "<<std::endl;
            break;
        default:break;
    }
    if(_state == Established)
    {
        _socket.shutdown();
    }
    _state = ClosedWait;
}

void CustomTCPConnection::close(const ShutdownReason& reason)
{
    shutdown(reason);
}

bool CustomTCPConnection::isflag(const char* buffer, const int len)
{
    if(len >= MIN_RECV_LEN)
    {
        return true;
    }
    else
    {
        return false;
    }

}


