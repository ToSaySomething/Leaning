#include "DbOperThread.h"

#include "Poco/NotificationQueue.h"
#include "Poco/Notification.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/JSON/Object.h"
#include <QDebug>

#include "ProtoToolHelper.h"
#include "Serialization.pb.h"
#include "SqlOper.h"
#include "DbOperNotification.h"
#include "Tool.h"
//#include "StreamSockectNotification.h"


using Poco::AutoPtr;
using Poco::NotificationQueue;
using Poco::Notification;
using tutorial::CmdData;
using Db::SqlOper;
using std::string;
using Poco::SharedPtr;
using Poco::JSON::Object;

DbOperThread::DbOperThread(NotificationQueue & _queue):queue(_queue){}

void DbOperThread::run(){
    try
    {
        do
        {
            string msg = Tool::fifoRead(Tool::db_pipe_name);
            if(msg.compare("") != 0)
            {
                Object db_obj = Tool::strToJson(msg);
                string return_msg = deal(ProtoToolHelper::jsonToCmdData(db_obj));
                Object sd_obj;
                sd_obj.set("ReturnMsg",return_msg);
                sd_obj.set("socketid",db_obj.get("socketid").convert<int>());
                string sd_msg = Tool::jsonToStr(sd_obj);
                Tool::fifoWrite(Tool::sd_pipe_name, sd_msg);
            }
        }while(true);
    }catch(Poco::Exception e)
    {
        qDebug()<<QString::fromStdString(e.displayText());
    }
}

string DbOperThread::deal(CmdData cd){
    if(cd.name() == CmdData::ProductObj_Name){
        table::BaseObj *buf_ptr = ProtoToolHelper::getBaseObj(cd);
        if(buf_ptr)
            qDebug()<<"p is not null\n";
//        if(static_cast<table::ProductObj*>(buf_ptr.get()))
//            qDebug()<<"put in is not null\n";
        table::ProductObj *p = static_cast<table::ProductObj*>(buf_ptr);
        if(cd.type() == CmdData::INSERT){
            SqlOper::insertData(p);
            string result = SqlOper::selectData(p);
            Tool::showMsgOnMainWindow("insertData\nId:"+
                                      Tool::intToString(p->getId())+
                                      "\tName:"+p->getName()+
                                      "\tValue:"+Tool::intToString(p->getValue())+
                                      "\n");
            delete p;
            return "Success\n" + result + "\n";
        }
        else if(cd.type() == CmdData::UPDATE){
            SqlOper::updateData(p);
            string result = SqlOper::selectData(p);
            Tool::showMsgOnMainWindow("updateData\nId:"+
                                      Tool::intToString(p->getId())+
                                      "\tName:"+p->getName()+
                                      "\tValue:"+Tool::intToString(p->getValue())+
                                      "\n");
            delete p;
            return "Success\n" + result + "\n";
        }
        else if (cd.type() == CmdData::DELETE){
            SqlOper::deleteData(p);
            string result = SqlOper::selectData(p);
            Tool::showMsgOnMainWindow("deleteData\nId:"+
                                      Tool::intToString(p->getId())+
                                      "\tName:"+p->getName()+
                                      "\tValue:"+Tool::intToString(p->getValue())+
                                      "\n");
            delete p;
            return "Success\n" + result + "\n";
        }
        else if(cd.type() == CmdData::SELECT){
            string result = SqlOper::selectData(p);
            delete p;
            return "Success\n" + result + "\n";
        }
        else{
            delete p;
            return "Something was Wrong";
        }
    }
    else{
        return "Something was Wrong";
    }
}


