
#include "connect.h"


Connection::Connection(const StreamSocket& s):
    ServerConnection(s), _state(ConnectionState::None),
    _socket(const_cast<StreamSocket&>(s)), _buff(new char[MAX_RECV_LEN])
{
}

Connection::~Connection()
{
}

bool Connection::onlyread()// read
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
        std::cout<< "Server: Sucessful receive: " << _buff << " from client: "<< _socket.peerAddress() <<std::endl;

        //send to client
        std::string data ="server received" ;
//        data += tra_message(data);
        _socket.sendBytes(data.data(), MAX_RECV_LEN, 0);
        return true;
    }
}

bool Connection::isflag(const char* buffer, const int len)
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

void Connection::run()
{
    Poco::Util::Application& app = Poco::Util::Application::instance();
    // 日志输出连接的TCP用户的地址（IP和端口）
    app.logger().information( "Request from " + _socket.peerAddress().toString() );
    _state = Connection::Established;//connect
    try
    {
        while(true)
        {
            if(_state == Connection::Established)
            {
                bool flag = _socket.poll(Poco::Timespan(TIME,0), Poco::Net::Socket::SelectMode::SELECT_READ);
                if(flag)
                {
                    if(!onlyread())
                    {
                        break;
                    }
                }
            }
            else if(_state == Connection::Closed)
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
/*
bool Connection::read()
{
    bool flag = true;
    onlyread();
    StatTimer *timer = new StatTimer();
    timer->start();
    std::cout << "--time start"<< std::endl;
    while(true)
    {
        if(readheardbeat())
        {   //update timer
           timer->settime(0);
           flag = true;
        }
        else
        {
            flag = false;
        }

        if (timer->end)
        {
            timer->stop();
            flag = false;
            break;
        }
    }
    return flag;
}

bool Connection::readheardbeat()
{
    if(!_socket.available())return false;
    int len = _socket.receiveBytes(_buff, MAX_RECV_LEN,0);
    std::cout << "*-len: "<<len << std::endl;
    if(0 >= len)
    {
        shutdown(CLIENT_CLOSE);// receive nothing
        return false;//closed socket
    }
    else
    {   //format is ill?
        bool flag = isflagformat(_buff, len);
        if(!flag)
        {
            std::cout << "*-ill format" <<std::endl;
            shutdown(ILLED_FORMAT);
            return false;
        }
        std::cout<< "Server: *-Sucessful receive from client " << _socket.peerAddress() <<std::endl;
        display_message(_buff);
        //send to client
        std::string data ="server received" ;
        _socket.sendBytes(data.data(), MAX_RECV_LEN, 0);
        return true;
    }
}

bool Connection::isflagformat(std::string buffer, const int len)
{
    if(len >= MIN_RECV_LEN)
    {
        std::string data = buffer;
        people::People p;
        p.ParseFromString(data);

        if(p.head() == "head" )
        {
            std::cout<<"head "<<std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Connection::display_message(std::string rece_string)
{
    std::string data = rece_string;
    people::People p;
    p.ParseFromString(data);
    std::cout << "----------------------- " << std::endl;
    std::cout << "| People: " << std::endl;
    std::cout << "| Head: " << p.head() << std::endl;
    std::cout << "| Name: " << p.name() << std::endl;
    std::cout << "| ID: " << p.id() << std::endl;
    std::cout << "| Email: " << p.email() << std::endl;
     std::cout << "---------------------- " << std::endl;
}

std::string Connection::tra_message(std::string data1)
{
    people::People p;
    p.set_head("head");
    p.set_name("Hideto");
    p.set_id("131232");
    p.set_email("hideto.bj@gmail.com");
    p.SerializeToString(&data1);
    return data1;
}
*/
void Connection::shutdown(const ShutdownReason& reason)
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

void Connection::close(const ShutdownReason& reason)
{
    shutdown(reason);
}

/*
bool CustomTCPConnection::read()
{
    onlyread();
    TimerExample example;

    Timer timer(0, 500);
    timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));

    while(true)
    {
        if(readheardbeat())
        {//update timer
           timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));
        }else{
            return false;
        }
    }
    return true;
}
*/



