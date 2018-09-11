#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include "people.pb.h"

#include <QMainWindow>
#include <iostream>

using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;

class MyClient{
public:
    const int LEN = 1024;
    const long long TIME = 2000;
    MyClient();
    ~MyClient(){}

public:
    bool isflag();
    void myconnect(char* ip, const int port);
    void send_(std::string strsend);
    QString send(std::string strsend);
    QString receive();

    std::string tral(std::string rece_string);
    void close();
    void setip(char* ip){
        _ipaddr = ip;
    }
    void setport(int port){
        _port = port;
    }

private:
    StreamSocket* _socket;
    std::string _ipaddr;
    int _port;

};

#endif // MYCLIENT_H
