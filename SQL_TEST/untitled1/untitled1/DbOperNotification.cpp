#include "DbOperNotification.h"
#include "Serialization.pb.h"

using tutorial::CmdData;

DbOperNotification::DbOperNotification(){}

DbOperNotification::DbOperNotification(int _id, CmdData _data):socket_id(_id),cmd_data(_data){}

CmdData DbOperNotification::getCmdData(){
    return this->cmd_data;
}

void DbOperNotification::setCmdData(CmdData _data){
    this->cmd_data = _data;
}

int DbOperNotification::getSocketId(){
    return this->socket_id;
}

void DbOperNotification::setSocketId(int id){
    this->socket_id = id;
}

Notification::Ptr DbOperNotification::getDbOperNotification(int _id, CmdData _data){
    Notification::Ptr ptr = new DbOperNotification(_id, _data);
    return ptr;
}
