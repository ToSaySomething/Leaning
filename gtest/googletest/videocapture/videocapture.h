/**
 * Copyright 2018 cloudwalk Inc.
 * author:hetb
 * time:2018-08-01
 */

#ifndef CW_VIDEO_CAPTURE_H
#define CW_VIDEO_CAPTURE_H

#ifdef _WIN32
#define CW_VIDEO_CAPTURE_API     __declspec(dllexport)
#define CW_VIDEO_CAPTURE_APICALL __stdcall
#else
#define CW_VIDEO_CAPTURE_API
#define CW_VIDEO_CAPTURE_APICALL
#endif

// 像素点格式
enum CW_ENUM_PIXEL_FORMAT {
    CW_PIXEL_FORMAT_YUV_420 = 0,   // YUV420
    CW_PIXEL_FORMAT_RGB_444,       // RGB444, 暂时不支持
};

// 视频抓拍设备类型
enum CW_ENUM_CAPTURE_DEVCIE_TYPE {
    CW_DEVICE_TYPE_HI3559A = 0,    // 海思3559AV100
    CW_DEVICE_TYPE_V4L2,           // linux标准V4L2, 暂时不支持
};

// 编码器句柄
#define CWVideoCaptureHandle void*

// 视频捕捉回调函数
typedef int (*fVideoCaptureDataCallBack)(CWVideoCaptureHandle captureHandle,const char* data,int dateLen);

// 日志回调
typedef int (*fVideoCaptureLogCallBack)(CWVideoCaptureHandle captureHandle,const char* log,int logLen);

#ifdef __cplusplus
extern "C"
{
#endif

/** 获取库版本信息
 *  @param [in] version  version
 *  @param [in] len      version长度
 *  @return 成功返回版本长度，失败返回 -1
 */
CW_VIDEO_CAPTURE_API int CW_VIDEO_CAPTURE_APICALL cwGetVideoCaptureVersion(char* version,int len);

/** 设置视频捕捉函数
 *  @param [in] func 视频捕捉回调函数
 */
CW_VIDEO_CAPTURE_API void CW_VIDEO_CAPTURE_APICALL cwSetVideoCaptureDataCallBack(fVideoCaptureDataCallBack func);

/** 设置日志回调
 *  @param [in] func 日志回调函数
 */
CW_VIDEO_CAPTURE_API void CW_VIDEO_CAPTURE_APICALL cwSetVideoCaptureLogCallBack(fVideoCaptureLogCallBack func);

/**
 *  打开视频设备
 *  @param [in]  deviceType  设备类型,参考CW_ENUM_CAPTURE_DEVCIE_TYPE
 *  @param [in]  channelId   通道编号，大于0
 *  @param [in]  frameRate   帧率（1-60）
 *  @param [in]  videoFormat 图像像素格式，参考CW_ENUM_PIXEL_FORMAT
 *  @return 编码器句柄
 */
CW_VIDEO_CAPTURE_API CWVideoCaptureHandle CW_VIDEO_CAPTURE_APICALL cwOpenVideoDevice(
    CW_ENUM_CAPTURE_DEVCIE_TYPE deviceType,
    unsigned int channelId,
    CW_ENUM_PIXEL_FORMAT videoFormat,
    unsigned int frameRate);

/**
 *  关闭视频设备
 *  @param [in]   VideoCaptureHandle 编码器句柄
 *  @return 成功返回0，失败返回小于0
 */
CW_VIDEO_CAPTURE_API int CW_VIDEO_CAPTURE_APICALL cwCloseVideoDevice(CWVideoCaptureHandle videoCaptureHandle);

#ifdef __cplusplus
}
#endif

#endif // CW_VIDEO_CAPTURE_H
