#ifndef API_PUSHER_MODULE_H
#define API_PUSHER_MODULE_H

#ifdef _WIN32
#define RTSP_PUSHER_API     __declspec(dllexport)
#define RTSP_PUSHER_APICALL __stdcall
#else
#define RTSP_PUSHER_API
#define RTSP_PUSHER_APICALL
#endif

#define RTSP_Pusher_Handler void*

typedef int (*fPushStreamStatusCallback)(RTSP_Pusher_Handler handler, int statusCode, void *context);

// 日志回调函数
typedef int (*fRtspPushStreamLogCallBack)(int logLevel,const char *logInfo,int len);


#ifdef __cplusplus
extern "C"
{
#endif

RTSP_PUSHER_API void RTSP_PUSHER_APICALL RTSP_Pusher_SetStartPort(unsigned int startPort=5000);

RTSP_PUSHER_API const char* RTSP_PUSHER_APICALL RTSP_Pusher_GetPushStreamLibVersion();

RTSP_PUSHER_API void RTSP_PUSHER_APICALL RTSP_Pusher_SetLogCallBack(fRtspPushStreamLogCallBack func);

RTSP_PUSHER_API int RTSP_PUSHER_APICALL RTSP_Pusher_SetStreamStatusCallback(fPushStreamStatusCallback cb, void* userContext);

// 创建rtsp推流句柄
RTSP_PUSHER_API RTSP_Pusher_Handler RTSP_PUSHER_APICALL RTSP_Pusher_Create();


RTSP_PUSHER_API int RTSP_PUSHER_APICALL RTSP_Pusher_StartStream(RTSP_Pusher_Handler handle,
        const char* url,
        int connType,
        const char* username,
        const char* password,
        int reconn);

// 功能:  推送码流
RTSP_PUSHER_API int RTSP_PUSHER_APICALL RTSP_Pusher_PushFrame(RTSP_Pusher_Handler handle);

// 关闭码流
RTSP_PUSHER_API int RTSP_PUSHER_APICALL RTSP_Pusher_StopStream(RTSP_Pusher_Handler handle);

// 释放推流句柄
RTSP_PUSHER_API int RTSP_PUSHER_APICALL RTSP_Pusher_Release(RTSP_Pusher_Handler handle);

#ifdef __cplusplus
}
#endif

#endif

