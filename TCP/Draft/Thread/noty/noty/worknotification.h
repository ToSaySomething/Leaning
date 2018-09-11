#ifndef WORKNOTIFICATION_H
#define WORKNOTIFICATION_H
#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
using Poco::Notification;
using Poco::NotificationQueue;

class WorkNotification: public Notification
{
public:
    WorkNotification(int data): _data(data) {}
    int data() const
    {
        return _data;
    }
private:
    int _data;
};


#endif // WORKNOTIFICATION_H
