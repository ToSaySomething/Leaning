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
    MyClient(){}
    ~MyClient(){}

    void myconnect(const char* ip, const int port);
    QString send(const char* ip, const int port,std::string strsend);

private:


};

#endif // MYCLIENT_H
