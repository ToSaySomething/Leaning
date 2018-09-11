#ifndef SERVER_H
#define SERVER_H

#include "ServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/SharedPtr.h"
#include <map>
#include "Poco/Thread.h"
#include "DbOperThread.h"
#include "SendMsgThread.h"
#include "unistd.h"

using Poco::Net::TCPServer;
using Poco::Net::TCPServerConnectionFactoryImpl;
using Poco::NotificationQueue;
using std::string;
using std::map;
using Poco::Net::StreamSocket;
using Poco::Thread;
using Poco::SharedPtr;


class Server{
    SharedPtr<Thread> dbop_thread1;
    SharedPtr<Thread> dbop_thread2;
    SharedPtr<Thread> sdop_thread1;
    SharedPtr<Thread> sdop_thread2;
    SharedPtr<DbOperThread> dbop;
    SharedPtr<SendMsgThread> sdop;
public:
    static NotificationQueue db_queue;
    static NotificationQueue send_queue;
    static map<int, StreamSocket*> conn_maps;
    static int map_id;
    TCPServer svr();
    Server(){
        dbop_thread1 = new Thread;
        dbop_thread2 = new Thread;
        sdop_thread1 = new Thread;
        sdop_thread2 = new Thread;
        dbop = new DbOperThread(db_queue);
        sdop = new SendMsgThread(send_queue);
    }
    ~Server(){}

    void openServer(string);
    void createPipe();

};

typedef TCPServerConnectionFactoryImpl<ServerConnection> TCPFactory;

#endif // SERVER_H
