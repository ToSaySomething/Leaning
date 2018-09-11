#ifndef DBOPERNOTIFICATION_H
#define DBOPERNOTIFICATION_H

#include "Poco/Notification.h"
#include "Serialization.pb.h"



using Poco::Notification;
using tutorial::CmdData;

class DbOperNotification : public Notification
{
private:
    int socket_id;
    CmdData cmd_data;
public:
    DbOperNotification();
    DbOperNotification(int, CmdData);
    CmdData getCmdData();
    void setCmdData(CmdData);
    int getSocketId();
    void setSocketId(int);
    static Notification::Ptr getDbOperNotification(int, CmdData);
};

#endif // DBOPERNOTIFICATION_H
