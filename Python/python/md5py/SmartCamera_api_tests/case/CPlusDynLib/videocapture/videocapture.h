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
enum CW_ENUM_PIXEL_FORMAT
{
	CW_PIXEL_FORMAT_YUV_420 = 0,   // YUV420
	CW_PIXEL_FORMAT_RGB_444,       // RGB444
};

// 编码器句柄
#define CWVideoCaptureHandle void*

// 视频捕捉回调函数
typedef int (*fVideoCaptureCallBack)(CWVideoCaptureHandle captureHandle,const char* data,int dateLen);

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
CW_VIDEO_CAPTURE_API void CW_VIDEO_CAPTURE_APICALL cwSetVideoCaptureCallBack(fVideoCaptureCallBack func);

/**
 *  打开视频设备
 *  @param [in]  deviceName  设备名称
 *  @param [in]  frameRate   帧率
 *  @param [in]  videoFormat 图像像素格式
 *  @return 编码器句柄
 */
CW_VIDEO_CAPTURE_API CWVideoCaptureHandle CW_VIDEO_CAPTURE_APICALL cwOpenVideoDevice(const char* deviceName,
 										     CW_ENUM_PIXEL_FORMAT videoFormat,
										     unsigned int frameRate);

/**
 *  关闭视频设备
 *  @param [in]   VideoCaptureHandle 编码器句柄
 *  @return 
 */
CW_VIDEO_CAPTURE_API int CW_VIDEO_CAPTURE_APICALL cwCloseVideoDevice(CWVideoCaptureHandle videoCaptureHandle);

#ifdef __cplusplus
}
#endif

#endif // CW_VIDEO_CAPTURE_H
