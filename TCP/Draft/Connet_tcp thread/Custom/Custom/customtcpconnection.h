#ifndef CUSTOMTCPCONNECTION_H
#define CUSTOMTCPCONNECTION_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Timespan.h"
#include "people.pb.h"

#include <string>
#include <iostream>


using Poco::Net::StreamSocket;
using Poco::Net::Socket;
using Poco::Net::TCPServerConnection;
using Poco::Timer;
using Poco::TimerCallback;

class CustomTCPConnection: public TCPServerConnection
{
    static const int MAX_RECV_LEN = 1024;
    static const int MIN_RECV_LEN = 2;
    static const long long TIME = 1000;
    enum ConnectionState
    {
        None,           // 无状态
        Established,    // 连接正常
        ClosedWait,     // 等待连接关闭
        Closed          // 连接已关闭
    };

    enum ShutdownReason
    {
        SERVICE_CLOSE = 5, //服务关闭连接
        CLIENT_CLOSE = 6, //关闭连接
        ILLED_FORMAT = 7 // 不合法的格式
    };

public:
    CustomTCPConnection(const StreamSocket& s);
    ~CustomTCPConnection();
    void run();

public:
    bool onlyread();
    void close(const ShutdownReason& reason);
    void shutdown(const ShutdownReason& reason);
    bool isflag(const char* buffer, const int len);
    void start_timer();
public:
    bool read();
    bool readheardbeat();
    bool isflagformat(std::string buffer, const int len);
    std::string tra_message(std::string data);
    void display_message(std::string rece_string);
private:
    ConnectionState _state;
    StreamSocket& _socket; 
    char* _buff;
};

#endif // CUSTOMTCPCONNECTION_H
