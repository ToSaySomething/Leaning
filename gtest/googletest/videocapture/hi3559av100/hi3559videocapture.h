#ifndef HI3559_VIDEO_CAPTURE_H
#define HI3559_VIDEO_CAPTURE_H

#include "customthread.h"

/**
 *  封装海思MPP多媒体框架VI,ISP,VPSS模块
 *  视频流走向：mipi -> isp --> vi --> vpss
 */
class Hi3559VideoCaptureWrap:public CustomThread
{
public:
    Hi3559VideoCaptureWrap() {}
    virtual ~Hi3559VideoCaptureWrap() {}

    // 初始化海思MPP
    static int initMPP();

    // 设置VI，VPSS工作模式
    int setVIVPSSWorkMode();

    // 启动及停止VI模块
    int startVI(unsigned int viDev = 0,unsigned int viPipe = 0,unsigned viChn = 0);
    int stopVi(unsigned int viDev = 0,unsigned int viPipe = 0,unsigned viChn = 0);

    // 启动及停止ISP模块
    int startISP(unsigned int viPipe = 0);
    virtual void run();
    int stopISP(unsigned int viPipe = 0);

    // 启动及停止VPSS模块
    int startVPSS(unsigned int vpssGrp = 0,unsigned int vpssChn = 0);
    int stopVPSS(unsigned int vpssGrp = 0,unsigned int vpssChn = 0);

    // 获取视频流
    int getVideoFrame(unsigned int vpssGrp, unsigned int vpssChn,
                      char* buffer,unsigned int bufferLen,unsigned int tWaitTimeout);

    // 反初始化海思MPP
    static int finiMPP();

protected:
    // 复位及设置mipi,cmos sensor时钟
    int startMipi();
    int stopMipi();

private:
    static bool bInitMPP_;     // 是否初始化MPP
};

#endif // HI3559_VIDEO_CAPTURE_H