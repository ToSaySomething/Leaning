/**
 *  Copyright 2018 cloudwalk Inc.
 *   author:hetb
 *   time:2018-08-01
 */
#ifndef CW_API_RTMP_PUSHER_H_
#define CW_API_RTMP_PUSHER_H_

#ifdef _WIN32
#define CW_RTMP_PUSHER_API     __declspec(dllexport)
#define CW_RTMP_PUSHER_APICALL __stdcall
#else
#define CW_RTMP_PUSHER_API
#define CW_RTMP_PUSHER_APICALL
#endif

#define RtspPusherHandler void*

#ifdef __cplusplus
extern "C"
{
#endif

/** 获取库版本信息
 *	@return 
 */
CW_RTMP_PUSHER_API const char* CW_RTMP_PUSHER_APICALL RtspPusherGetPushStreamLibVersion();

/** 创建推流器
 *	@return 
 */
CW_RTMP_PUSHER_API RTSP_Pusher_Handler CW_RTMP_PUSHER_APICALL RtspPusherCreate();

/** 启动推流
 *	@return 
 */
CW_RTMP_PUSHER_API int CW_RTMP_PUSHER_APICALL RtspPusherStartStream(RtspPusherHandler handle,
			const char* url,
			int connType,
			const char* username,
			const char* password,
			int reconn);

/** 推送码流
 *	@return 
 */
CW_RTMP_PUSHER_API int CW_RTMP_PUSHER_APICALL RtspPusherPushFrame(RtspPusherHandler handle);

/** 停止推流
 *	@return 
 */
CW_RTMP_PUSHER_API int CW_RTMP_PUSHER_APICALL RtspPusherStopStream(RtspPusherHandler handle);

/** 释放推流资源
 *	@return 
 */
CW_RTMP_PUSHER_API int CW_RTMP_PUSHER_APICALL RtspPusherRelease(RtspPusherHandler handle);

#ifdef __cplusplus
}
#endif

#endif   // CW_API_RTMP_PUSHER_H_


