#include "SendMsgThread.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Notification.h"
#include "Poco/AutoPtr.h"
#include <QDebug>
#include "ProtoToolHelper.h"
#include "Serialization.pb.h"
#include "SqlOper.h"
#include "StreamSockectNotification.h"
#include "Tool.h"
#include "Server.h"
#include "StreamSockectNotification.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/SharedPtr.h"
#include "Poco/JSON/Object.h"

using Poco::AutoPtr;
using Poco::NotificationQueue;
using Poco::Notification;
using Poco::Net::StreamSocket;
using Poco::SharedPtr;
using Poco::JSON::Object;
using tutorial::CmdData;
using Db::SqlOper;
using std::string;


SendMsgThread::SendMsgThread(NotificationQueue& _queue):queue(_queue){}

void SendMsgThread::run(){
    try
    {
        do{
            string msg = Tool::fifoRead(Tool::sd_pipe_name);
            if(msg.compare("") != 0){
                Object obj = Tool::strToJson(msg);
                deal(obj.get("ReturnMsg").toString(), obj.get("socketid").convert<int>());
            }
        }while(true);
    }catch(Poco::Exception e)
    {
        QString::fromStdString(e.displayText());
    }
}

void SendMsgThread::deal(string msg, int id){

    map<int, StreamSocket*>::iterator it = Server::conn_maps.begin();
    it = Server::conn_maps.find(id);
    if(it!=Server::conn_maps.end()){
        StreamSocket* ss = Server::conn_maps[id];
        ss->sendBytes(msg.c_str(), msg.length());
        Tool::showMsgOnMainWindow("Send Success\n");
    }
    else{
        Tool::showMsgOnMainWindow("Cannot find this client\n");
    }


}
