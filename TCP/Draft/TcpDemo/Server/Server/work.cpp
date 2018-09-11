
#include "work.h"


void Worker::run()
{
    AutoPtr<Notification> pNf(_queue.waitDequeueNotification());
    while (pNf)
    {
        WorkNotification* pWorkNf =
            dynamic_cast<WorkNotification*>(pNf.get());
        if (pWorkNf)
        {
            //do
            printf("hi!\n");

        }
        pNf = _queue.waitDequeueNotification();
    }
}

void Worker::rece(StreamSocket socket)
{
    char buff[LEN];
    int len = socket.receiveBytes(buff, LEN);
    if(len <= 0)
    {
        std::cout << "len<= 0" << std::endl;
    }
    else
    {
        std::cout << "Server: receive "<< buff<<" " << socket.peerAddress() << std::endl;
    }
}

void Worker::send(StreamSocket socket)
{
    char buff1[LEN] = "receive from server";
    socket.sendBytes(buff1, LEN);
}
