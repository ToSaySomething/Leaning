#include "Server.h"

#include "Poco/Net/TCPServer.h"
#include "Poco/NumberParser.h"
#include "Poco/Thread.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/NotificationQueue.h"
#include "qdebug.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/wait.h"
#include "fcntl.h"

#include "ServerConnection.h"
#include "ServerConnectionFactory.h"
#include "DbOperThread.h"
#include "SendMsgThread.h"
#include "Tool.h"



using Poco::Net::TCPServer;
using Poco::NumberParser;
using Poco::Exception;
using Poco::Thread;
using Poco::Net::StreamSocket;
using Poco::NotificationQueue;
using std::string;

map<int, StreamSocket*> Server::conn_maps;
NotificationQueue Server::db_queue;
NotificationQueue Server::send_queue;
int Server::map_id = 0;

void Server::openServer(string m_port){
    try{
        Poco::UInt16 port = NumberParser::parse(m_port);
        Tool::showMsgOnMainWindow("Set port:" + Tool::intToString(port) + "\n");
//        TCPServer srv();
//        srv.start();
        if(Tool::createFifo()){
            Tool::showMsgOnMainWindow("Pipe Create Success\n");
        }
//        int pid = fork();
//        if(pid = 0){
//            int a;
//            dbop_thread1.get()->start(*(sdop.get()));
//            while(true){}
//        }
//        else{
            sdop_thread1.get()->start(*(sdop.get()));
//        sdop_thread2.start(sdop);
            TCPServer *pServer = new TCPServer(new ServerConnectionFactory(), port);
            pServer->start();
            Tool::showMsgOnMainWindow("Listening...\n");
//        }
    }
    catch (Exception& exc){
        Tool::showMsgOnMainWindow(exc.displayText()+"\n");
    }
}

