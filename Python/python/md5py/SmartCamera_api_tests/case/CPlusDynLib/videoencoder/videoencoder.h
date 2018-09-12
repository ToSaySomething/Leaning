/**
 *  Copyright 2018 cloudwalk Inc.
 *   author:hetb
 *   time:2018-08-01
 */

#ifndef CW_API_VIDEO_ENCODER_H_
#define CW_API_VIDEO_ENCODER_H_

#ifdef _WIN32
#define CW_VIDEO_ENCODER_API     __declspec(dllexport)
#define CW_VIDEO_ENCODER_APICALL __stdcall
#else
#define CW_VIDEO_ENCODER_API
#define CW_VIDEO_ENCODER_APICALL
#endif

// 编码类型
enum CW_VIDEO_ENCODE_TYPE
{
    // 264编码类型
    CW_ENCODE_TYPE_HIS3556A_H264 = 1,   // his3556A H264 硬编码器
    CW_ENCODE_TYPE_X264,                // x264软编码器
    // 265编码类型 
    CW_ENCODE_TYPE_HIS3556A_H265,       // his3556A H265 硬编码器
    CW_ENCODE_TYPE_X265,                // x265软编码器
};

// 编码器句柄
#define CWEncoderHandle void*

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *  创建编码器
 *  @param [in ] encoderType 编码器类型
 *  @return 编码器句柄
 */
CW_VIDEO_ENCODER_API CWEncoderHandle CW_VIDEO_ENCODER_APICALL cwCreateEncoder(CW_VIDEO_ENCODE_TYPE encoderType);


/**
 *  编码一帧数据
 *  参数： encoderHandle - 编码器句柄
 *  @return 
 */
CW_VIDEO_ENCODER_API CWEncoderHandle CW_VIDEO_ENCODER_APICALL cwEncoderOneFrame(CWEncoderHandle encoderHandle,
											const char* srcVideoData,unsigned int srcVideoDataLen,
											const char* encoderData,unsigned int encoderDataLen);

/**
 *  销毁编码器
 *  @param [in ] encoderHandle - 编码器句柄
 *  @return 
 */
CW_VIDEO_ENCODER_API int CW_VIDEO_ENCODER_APICALL cwDestroyEncoder(CWEncoderHandle encoderHandle);


#ifdef __cplusplus
}
#endif

#endif   // CW_API_VIDEO_ENCODER_H_
