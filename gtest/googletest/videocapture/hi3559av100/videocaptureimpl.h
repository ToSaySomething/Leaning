#ifndef HI3559A_VIDEO_CAPTURE_IMPL_H
#define HI3559A_VIDEO_CAPTURE_IMPL_H

#include <pthread.h>

#include "videocaptureinterface.h"
#include "hi3559videocapture.h"
#include "customthread.h"

/**
 * hi3559A摄像头捕获接口实现类
 */
class Hi3559AVideoCaptureImpl:public VideoCaptureInterface,public Hi3559VideoCaptureWrap
{
public:
    Hi3559AVideoCaptureImpl():bThreadExit_(true) {}

    virtual int open(unsigned int channelId,
                     CW_ENUM_PIXEL_FORMAT videoFormat,
                     unsigned int frameRate);

    virtual int onRecvData(const char* buffer,unsigned int bufferLen);

    virtual int close();

    inline bool getThreadExit() const
    {
        return bThreadExit_;
    }

private:
    pthread_t workThreadId_;
    bool bThreadExit_;
};

#endif // HI3559A_VIDEO_CAPTURE_IMPL_H

