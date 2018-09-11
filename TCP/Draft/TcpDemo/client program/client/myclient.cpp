#include "myclient.h"
#include "config.h"


#include <iostream>



void MyClient::myconnect(const char* ip, const int port){
    SocketAddress sa(ip, port); // the server port.
    Poco::Net::StreamSocket socket(sa);
}

QString MyClient::send(const char* ip, const int port,std::string strsend){
    //send

    SocketAddress sa(ip, port); // the server port.
    Poco::Net::StreamSocket socket(sa);
    Poco::Net::SocketStream str(socket);

    int len = socket.sendBytes(strsend.c_str(), strsend.length());
    if(len < 0){
        std::cout << "send write error" << std::endl;
    }

    socket.shutdownSend();//closed send

    char rece[1024]={0};
    int len1 = socket.receiveBytes(rece, 1024);
    std::cout << "re:" << rece << std::endl;

    QString reQString = QString::fromStdString(rece);
    return reQString;

    //socket.shutdownReceive();//closed re
    // Writes all bytes readable from str into std::cout, using an internal buffer.
    //Poco::StreamCopier::copyStream(str, std::cout);
}


