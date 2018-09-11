#include "myclient.h"
#include "config.h"
#include "people.pb.h"
#include "people.pb.cc"

#include <iostream>
#include <string>

const long long TIME = 0xfffffffffff;
using namespace std;

MyClient::MyClient(): _socket (nullptr),_ipaddr(""),_port(0)
{
    cnt = 0;
}

void MyClient::myconnect(char* ip, const int port)
{
    setip(ip);
    setport(port);
    cnt++;
    SocketAddress sa(_ipaddr, _port); // the server port.
    _socket = new Poco::Net::StreamSocket (sa);
    std::string strsend = " *hello* ";
    int len = _socket->sendBytes(strsend.c_str(), strsend.length());
    std::cout<<cnt<<std::endl;
}

void MyClient::close()
{
    _socket->shutdown();
    _socket->close();
}

void MyClient::send1(std::string strsend)
{//send
    Poco::Timespan stimeout( TIME );
    _socket->setReceiveTimeout(stimeout);
    int len = _socket->sendBytes(strsend.c_str(), strsend.length());
    if(len < 0){
        std::cout << "client: send error" << std::endl;
    }
    //return receive();
}

QString MyClient::send(std::string strsend)
{//send
    Poco::Timespan stimeout( TIME );
    _socket->setReceiveTimeout(stimeout);
    int len = _socket->sendBytes(strsend.c_str(), strsend.length());
    if(len < 0){
        std::cout << "client: send error" << std::endl;
    }
    return receive();
}

QString MyClient::receive()
{//receive
    char rece[1024]={""};

    int len1 = _socket->receiveBytes(rece, 1024);
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

    cout << "People: " << endl;
    cout << "Name: " << p.name() << endl;
    cout << "ID: " << p.id() << endl;
    cout << "Email: " << p.email() << endl;
    return data;
}
