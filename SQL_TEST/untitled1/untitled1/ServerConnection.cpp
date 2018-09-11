#include "ServerConnection.h"

#include <QDebug>
#include <QString>
#include <map>

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/StreamSocket.h"
#include "Tool.h"
#include "ProtoToolHelper.h"
#include "Server.h"
#include "DbOperNotification.h"
#include "Poco/SharedPtr.h"

using Poco::Net::TCPServer;
using Poco::Net::StreamSocket;
using Poco::Exception;
using Poco::SharedPtr;

using std::string;
using std::pair;

using tutorial::CmdData;


void ServerConnection::run(){
    StreamSocket& ss = socket();
    try
    {
        int id = (++Server::map_id);
        StreamSocket* p_ss = &ss;
        Server::conn_maps.insert(std::make_pair(id, p_ss));
        char buffer[1024] = {0};
        int n;
        while(true){
            n = ss.receiveBytes(buffer, sizeof(buffer));
            if(n>0){
                Tool::showMsgOnMainWindow("Received " + Tool::intToString(n) + " bytes\n");
                qDebug()<<"Received "<<QString::fromStdString(Tool::intToString(n) )<<" bytes\n";
                string msg(buffer);
                qDebug()<<QString::fromStdString(msg);
                if(msg.compare("HeartBeat") == 0)
                    Tool::showMsgOnMainWindow("HeartBeat..\n");
                else
                    myDeal(msg,id);
    //            int len = ss.sendBytes(strsend.c_str(), strsend.length());
    //            if(len<0)
    //                Tool::showMsgOnMainWindow("Send Failed\n");
            }
            else{
                return;
            }
        }
    }
    catch (Exception& exc)
    {
        Tool::showMsgOnMainWindow("ClientConnection: " + exc.displayText() + "\n");
    }
}

string ServerConnection::myDeal(string msg, int id){
    CmdData cd = ProtoToolHelper::StringToCmdData(msg);
    Object obj;
    obj.set("ObjName",cd.name());
    obj.set("CmdType",cd.type());
    obj.set("tablename",cd.product().tablename());
    obj.set("id",cd.product().id());
    obj.set("name",cd.product().name());
    obj.set("value",cd.product().value());
    obj.set("socketid",id);
    Tool::jsonToStr(obj);
    return "";
}

