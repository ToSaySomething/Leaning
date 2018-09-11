#include "myclient.h"
#include "config.h"
#include "people.pb.h"
#include "people.pb.cc"

#include <iostream>
#include <string>

MyClient::MyClient(): _socket (nullptr),_ipaddr(""),_port(0)
{
}

void MyClient::myconnect(char* ip, const int port)
{
    setip(ip);
    setport(port);

//    for(int t = 0; t < 3; t++)
//    {
        SocketAddress sa(_ipaddr, _port); // the server port.
        _socket = new Poco::Net::StreamSocket (sa);
        std::string strsend = {"***client request***\n"};
        _socket->sendBytes(strsend.c_str(), strsend.length());
//    }

}

void MyClient::close()
{
    _socket->close();
    std::cout << " client end " << std::endl;
}

bool MyClient::isflag()
{   //is connect?
    if( _socket->poll(Poco::Timespan(TIME,0), Poco::Net::Socket::SelectMode::SELECT_READ) )
        return true;
    else
        return false;

}

void MyClient::send_(std::string strsend)
{   //send

    int len = _socket->sendBytes(strsend.c_str(), strsend.length());
    if(len < 0)
    {
        std::cout << "client: send error" << std::endl;
    }
}


QString MyClient::send(std::string strsend)
{//send

    int len = _socket->sendBytes(strsend.c_str(), strsend.length());
    if(len < 0)
    {
        std::cout << "client: send error" << std::endl;
    }
    return receive();
}

QString MyClient::receive()
{//receive
    char rece[LEN]={""};

    int len1 = _socket->receiveBytes(rece, LEN);
    if(len1 == 0){
        std::cout << "client: receive error" << std::endl;
        return NULL;
    }

    std::cout << "client receive: " << rece << std::endl;

    QString reQString = QString::fromStdString(rece);
    return reQString;
}

std::string MyClient::tral(std::string rece_string){
    std::string data = rece_string;
    people::People p;
    p.ParseFromString(data);

    std::cout << "People: " << std::endl;
    std::cout << "Name: " << p.name() << std::endl;
    std::cout << "ID: " << p.id() << std::endl;
    std::cout << "Email: " << p.email() << std::endl;
    return data;
}
