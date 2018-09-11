
#include "StreamSockectNotification.h"
#include "Serialization.pb.h"

using tutorial::CmdData;
using std::string;

StreamSockectNotification::StreamSockectNotification(){}

StreamSockectNotification::StreamSockectNotification(int _id, string _msg):sockect_id(_id),msg(_msg){}

int StreamSockectNotification::getSockectId(){
    return this->sockect_id;
}

void StreamSockectNotification::setSockectId(int _id){
    this->sockect_id = _id;
}

string StreamSockectNotification::getMsg(){
    return this->msg;
}

void StreamSockectNotification::setMsg(string _msg){
    this->msg = _msg;
}

Notification::Ptr StreamSockectNotification::getStreamSockectNotification(int _id, string _msg){
    Notification::Ptr ptr = new StreamSockectNotification(_id, _msg);
    return ptr;
}
