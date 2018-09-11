#ifndef VIDEO_CAPTURE_INTERFACE_H
#define VIDEO_CAPTURE_INTERFACE_H

#include <stdlib.h>
#include <string.h>
#include "videocapture.h"

class VideoCaptureInterface
{
public:
    VideoCaptureInterface()  {}
    virtual ~VideoCaptureInterface() {}

public:
    virtual int open(unsigned int channelId,
                     CW_ENUM_PIXEL_FORMAT videoFormat,
                     unsigned int frameRate) = 0;
    virtual int onRecvData(const char* buffer,unsigned int bufferLen) = 0;
    virtual int close() = 0;
	static void throwLog();

public:
    static void setVideoCaptureDataCallBack(fVideoCaptureDataCallBack func)
    {
        interfaceDataCallBackFunc_ = func;
    }

    static fVideoCaptureDataCallBack getVideoCaptureDataCallBack()
    {
        return interfaceDataCallBackFunc_;
    }

    static void setVideoCaptureLogCallBack(fVideoCaptureLogCallBack func)
    {
        interfaceLogCallBackFunc_ = func;
    }

    static fVideoCaptureDataCallBack getVideoCaptureLogCallBack()
    {
        return interfaceLogCallBackFunc_;
    }

private:
    static fVideoCaptureDataCallBack interfaceDataCallBackFunc_;
    static fVideoCaptureLogCallBack interfaceLogCallBackFunc_;
};

#endif // VIDEO_CAPTURE_INTERFACE_H
