#include "videocapture.h"
#include "videocaptureinterface.h"
#include "basedatatype.h"
#include "hi3559av100/videocaptureimpl.h"

#define VIDEO_CAPTURE_VERSION   "1.0.0"

int CW_VIDEO_CAPTURE_APICALL cwGetVideoCaptureVersion(char* version,int len)
{
    if(NULL == version || len <= 0)
        return CW_RET_FAILED;
    strcpy(version,VIDEO_CAPTURE_VERSION);
    return strlen(VIDEO_CAPTURE_VERSION);
}

void CW_VIDEO_CAPTURE_APICALL cwSetVideoCaptureDataCallBack(fVideoCaptureDataCallBack func)
{
    VideoCaptureInterface::setVideoCaptureDataCallBack(func);
}

void CW_VIDEO_CAPTURE_APICALL cwSetVideoCaptureLogCallBack(fVideoCaptureLogCallBack func)
{
    VideoCaptureInterface::setVideoCaptureLogCallBack(func);
}

CWVideoCaptureHandle CW_VIDEO_CAPTURE_APICALL cwOpenVideoDevice(CW_ENUM_CAPTURE_DEVCIE_TYPE deviceType,
        unsigned int channelId,
        CW_ENUM_PIXEL_FORMAT videoFormat,
        unsigned int frameRate)
{
    VideoCaptureInterface *videoCaptureInterface = NULL;
    if(channelId<0 || videoFormat < CW_PIXEL_FORMAT_YUV_420 ||
       videoFormat > CW_PIXEL_FORMAT_RGB_444 || frameRate < 0 || frameRate > 30)
        return NULL;
    switch(deviceType) {
        case CW_DEVICE_TYPE_HI3559A: {
            if(CW_PIXEL_FORMAT_YUV_420 == videoFormat) {
                videoCaptureInterface = new Hi3559AVideoCaptureImpl;
            }
        }
        break;
        case CW_DEVICE_TYPE_V4L2:
            break;
        default:
            break;
    }
    if(NULL != videoCaptureInterface) {
        if(CW_RET_SUCCESS == videoCaptureInterface->open(channelId,videoFormat,frameRate)) {
            return videoCaptureInterface;
        }
    }
    return NULL;
}

int CW_VIDEO_CAPTURE_APICALL cwCloseVideoDevice(CWVideoCaptureHandle videoCaptureHandle)
{
    if(NULL == videoCaptureHandle)
        return CW_RET_FAILED;
    VideoCaptureInterface *videoCaptureInterface = static_cast<VideoCaptureInterface*>(videoCaptureHandle);
    if(videoCaptureInterface != NULL) {
        videoCaptureInterface->close();
        delete videoCaptureInterface;
        videoCaptureInterface = NULL;
        return CW_RET_SUCCESS;
    }
    return CW_RET_FAILED;
}



