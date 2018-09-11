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
            printf("hi!\n");
        //    Sleep(100);
        }
        pNf = _queue.waitDequeueNotification();
    }
}
