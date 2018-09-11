#include <iostream>

#include "videocaptureimpl.h"
#include "basedatatype.h"

using namespace std;

// 视频帧最大长度
#define VIDEO_FRAME_MAX_LEN              4000*3200

// 读取视频帧最大超时时间
#define READ_VIDEO_FRAME_MAX_TIMEOUT     2000

void *Hi3559WorkThread(void* threadContext)
{
    unsigned int tWaitTimeout = READ_VIDEO_FRAME_MAX_TIMEOUT;
    if(NULL == threadContext)
        return NULL;
    Hi3559AVideoCaptureImpl *hi3559AVideoCaptureImpl = static_cast<Hi3559AVideoCaptureImpl*>(threadContext);
    if(NULL != hi3559AVideoCaptureImpl) {
        char *buffer = (char*)malloc(VIDEO_FRAME_MAX_LEN*sizeof(char));
        unsigned int bufferLen = VIDEO_FRAME_MAX_LEN;
        do {
            memset(buffer,0,VIDEO_FRAME_MAX_LEN*sizeof(char));
            int ret = hi3559AVideoCaptureImpl->getVideoFrame(0,0,buffer,bufferLen,tWaitTimeout);
            if(ret > 0) {
                hi3559AVideoCaptureImpl->onRecvData(buffer,ret);
            }
            if(hi3559AVideoCaptureImpl->getThreadExit())
                break;
        } while(true);
        free(buffer);
        buffer = NULL;
    }
	std::cout<<"read video frame thread exit."<<std::endl;
    return NULL;
}

int Hi3559AVideoCaptureImpl::open(unsigned int channelId,
                                  CW_ENUM_PIXEL_FORMAT videoFormat,
                                  unsigned int frameRate)
{
    if( CW_RET_SUCCESS != Hi3559VideoCaptureWrap::initMPP() )
        return CW_RET_FAILED;

    if(CW_RET_SUCCESS != this->setVIVPSSWorkMode()) {
        goto MPP_ERROR;
    }
    std::cout<<"setVIVPSSWorkMode success."<<std::endl;

    if(CW_RET_SUCCESS != this->startVI()) {
        goto MPP_ERROR;
    }
    std::cout<<"startVI success."<<std::endl;

    if(CW_RET_SUCCESS != this->startISP()) {
        goto VI_ERROR;
    }
    std::cout<<"startISP success."<<std::endl;

    if(CW_RET_SUCCESS != this->startVPSS()) {
        goto ISP_ERROR;
    }
    std::cout<<"startVPSS success."<<std::endl;

    bThreadExit_ = false;

    // 启动线程
    pthread_create(&workThreadId_,NULL,Hi3559WorkThread,(void*)this);

    return CW_RET_SUCCESS;

VI_ERROR:
    this->stopVi();
ISP_ERROR:
    this->stopISP();
MPP_ERROR:
    this->finiMPP();

    return CW_RET_FAILED;
}

int Hi3559AVideoCaptureImpl::onRecvData(const char* buffer,unsigned int bufferLen)
{
    fVideoCaptureDataCallBack fVideoCaptrueCallBack = this->getVideoCaptureDataCallBack();
    if(fVideoCaptrueCallBack != NULL) {
        fVideoCaptrueCallBack(this,buffer,bufferLen);
    }
    return CW_RET_SUCCESS;
}

int Hi3559AVideoCaptureImpl::close()
{
    bThreadExit_ = true;
    pthread_join(workThreadId_,NULL);
    if(CW_RET_SUCCESS != this->stopVPSS()) {
        std::cout<<"call stopVPSS failed."<<std::endl;
    }
    if(CW_RET_SUCCESS != this->stopISP()) {
        std::cout<<"call stopISP failed."<<std::endl;
    }
    if(CW_RET_SUCCESS != this->stopVi()) {
        std::cout<<"call stopVi failed."<<std::endl;
    }
    if(CW_RET_SUCCESS != this->finiMPP()) {
        std::cout<<"call finiMPP failed."<<std::endl;
    }
    return CW_RET_SUCCESS;
}

