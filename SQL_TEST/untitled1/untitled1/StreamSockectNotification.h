#ifndef STREAMSOCKECTNOTIFICATION_H
#define STREAMSOCKECTNOTIFICATION_H

#include "Poco/Notification.h"

using Poco::Notification;
using std::string;

class StreamSockectNotification : public Notification
{
private:
    int sockect_id;
    string msg;
public:
    StreamSockectNotification();
    StreamSockectNotification(int,string);
    int getSockectId();
    void setSockectId(int);
    string getMsg();
    void setMsg(string);
    static Notification::Ptr getStreamSockectNotification(int,string);
};

#endif // STREAMSOCKECTNOTIFICATION_H
