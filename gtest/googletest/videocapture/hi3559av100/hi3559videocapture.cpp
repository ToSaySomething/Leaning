#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/prctl.h>

#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include <iostream>

#include "hi_comm_sys.h"
#include "hi_comm_vb.h"
#include "hi_comm_video.h"
#include "hi_comm_vi.h"
#include "hi_buffer.h"
#include "hi_mipi.h"
#include "mpi_vb.h"
#include "mpi_vi.h"
#include "mpi_sys.h"
#include "mpi_vpss.h"
#include "hi_comm_isp.h"
#include "hi_sns_ctrl.h"
#include "hi_ae_comm.h"
#include "hi_awb_comm.h"
#include "mpi_isp.h"
#include "mpi_ae.h"
#include "mpi_awb.h"

#include "hi3559videocapture.h"

using namespace std;

#define MIPI_DEV_NODE          "/dev/hi_mipi"

#define SAMPLE_PIXEL_FORMAT    PIXEL_FORMAT_YVU_SEMIPLANAR_420

#define ENABLE_WRITE_FILE    0

combo_dev_attr_t MIPI_4lane_CHN0_SENSOR_IMX334_12BIT_8M_NOWDR_ATTR = {
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    .data_rate = MIPI_DATA_RATE_X1,
    .img_rect = {0, 0, 3840, 2160},

    {
        .mipi_attr =
        {
            DATA_TYPE_RAW_12BIT,
            HI_MIPI_WDR_MODE_NONE,
            {0, 1, 2, 3, -1, -1, -1, -1}
        }
    }
};

VI_DEV_ATTR_S DEV_ATTR_IMX334_8M_BASE = {
    VI_MODE_MIPI,
    VI_WORK_MODE_1Multiplex,
    {0xFFC00000,    0x0},
    VI_SCAN_PROGRESSIVE,
    {-1, -1, -1, -1},
    VI_DATA_SEQ_YUYV,

    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_LOW, VI_HSYNC_VALID_SINGNAL,VI_HSYNC_NEG_HIGH,VI_VSYNC_VALID_SINGAL,VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1280,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            720,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    VI_DATA_TYPE_RGB,
    HI_FALSE,
    {3840, 2160},
    {
        {
            {3840, 2160},
        },
        {
            VI_REPHASE_MODE_NONE,
            VI_REPHASE_MODE_NONE
        }
    },
    {
        WDR_MODE_NONE,
        2160
    },
    DATA_RATE_X1
};

VI_PIPE_ATTR_S PIPE_ATTR_3840x2160_RAW12_420_3DNR_RFR = {
    VI_PIPE_BYPASS_NONE, HI_FALSE,HI_FALSE,
    3840, 2160,
    PIXEL_FORMAT_RGB_BAYER_12BPP,
    COMPRESS_MODE_LINE,
    DATA_BITWIDTH_12,
    HI_TRUE,
    {
        PIXEL_FORMAT_YVU_SEMIPLANAR_420,
        DATA_BITWIDTH_8,
        VI_NR_REF_FROM_RFR,
        COMPRESS_MODE_NONE
    },
    HI_FALSE,
    { -1, -1}
};

VI_CHN_ATTR_S CHN_ATTR_3840x2160_420_SDR8_LINEAR = {
    {3840, 2160},
    PIXEL_FORMAT_YVU_SEMIPLANAR_420,
    DYNAMIC_RANGE_SDR8,
    VIDEO_FORMAT_LINEAR,
    COMPRESS_MODE_NONE,
    HI_FALSE,      HI_FALSE,
    0,
    { -1, -1}
};

ISP_PUB_ATTR_S ISP_PUB_ATTR_IMX334_4K_30FPS = {
    {0, 0, 3840, 2160},
    {3840, 2160},
    30,
    BAYER_RGGB,
    WDR_MODE_NONE,
    0,
};

bool Hi3559VideoCaptureWrap::bInitMPP_ = false;

int Hi3559VideoCaptureWrap::initMPP()
{
    HI_S32 s32Ret = HI_FAILURE;
    if(bInitMPP_)
        return HI_SUCCESS;

    HI_MPI_SYS_Exit();
    HI_MPI_VB_Exit();

    // 设置VB属性
    VB_CONFIG_S stVbConf;
    HI_U32 u32BlkSize = 0;
    hi_memset(&stVbConf, sizeof(VB_CONFIG_S), 0, sizeof(VB_CONFIG_S));
    stVbConf.u32MaxPoolCnt = 2;
    u32BlkSize = COMMON_GetPicBufferSize(3840, 2160,
                                         SAMPLE_PIXEL_FORMAT,
                                         DATA_BITWIDTH_10,
                                         COMPRESS_MODE_SEG,
                                         DEFAULT_ALIGN);
    stVbConf.astCommPool[0].u64BlkSize  = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt   = 10;
    u32BlkSize = VI_GetRawBufferSize(3840, 2160,
                                     PIXEL_FORMAT_RGB_BAYER_16BPP,
                                     COMPRESS_MODE_NONE,
                                     DEFAULT_ALIGN);
    stVbConf.astCommPool[1].u64BlkSize  = u32BlkSize;
    stVbConf.astCommPool[1].u32BlkCnt   = 4;
    s32Ret = HI_MPI_VB_SetConfig(&stVbConf);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VB_SetConfig failed."<<std::endl;
        return s32Ret;
    }

    // 初始化VB
    s32Ret = HI_MPI_VB_Init();
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VB_Init failed."<<std::endl;
        return s32Ret;
    }

    // MPI系统初始化
    s32Ret = HI_MPI_SYS_Init();
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_SYS_Init failed."<<std::endl;
        return s32Ret;
    }

    bInitMPP_ = true;

    return HI_SUCCESS;
}

int Hi3559VideoCaptureWrap::finiMPP()
{
    HI_S32 s32Ret = HI_FAILURE;
    if(bInitMPP_) {
        s32Ret = HI_MPI_SYS_Exit();
        if(HI_SUCCESS != s32Ret) {
            std::cout<<"call HI_MPI_SYS_Exit failed."<<std::endl;
            return s32Ret;
        }

        s32Ret = HI_MPI_VB_Exit();
        if(HI_SUCCESS != s32Ret) {
            std::cout<<"call HI_MPI_SYS_Exit failed."<<std::endl;
            return s32Ret;
        }
        bInitMPP_ = false;
    }
    return HI_SUCCESS;
}


int Hi3559VideoCaptureWrap::startMipi()
{
    HI_S32 fd;
    HI_S32 s32Ret = HI_FAILURE;
    combo_dev_t devno = 0;
    fd = ::open(MIPI_DEV_NODE, O_RDWR);
    if (fd < 0) {
        return HI_FAILURE;
    }

    // set mipi hs model    SAMPLE_COMM_VI_SetMipiHsMode
    int enHsMode = LANE_DIVIDE_MODE_7;
    s32Ret = ioctl(fd, HI_MIPI_SET_HS_MODE, &enHsMode);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"mipi init: set hs model failed"<<std::endl;
        goto MIPI_INIT;
    }

    // enable mipi clock  SAMPLE_COMM_VI_EnableMipiClock
    s32Ret = ioctl(fd, HI_MIPI_ENABLE_MIPI_CLOCK, &devno);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"mipi init: enable mipi clock failed"<<std::endl;
        goto MIPI_INIT;
    }

    // reset mipi  SAMPLE_COMM_VI_ResetMipi
    s32Ret = ioctl(fd, HI_MIPI_RESET_MIPI, &devno);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"mipi init: reset mipi failed"<<std::endl;
        goto MIPI_INIT;
    }

    // enable sensor clock  SAMPLE_COMM_VI_EnableSensorClock
    for (sns_rst_source_t snsDev = 0; snsDev < SNS_MAX_CLK_SOURCE_NUM; snsDev++) {
        s32Ret = ioctl(fd, HI_MIPI_ENABLE_SENSOR_CLOCK, &snsDev);
        if (HI_SUCCESS != s32Ret) {
            std::cout<<"mipi init: enable sensor clock failed"<<std::endl;
            goto MIPI_INIT;
        }
    }

    // reset sensor   SAMPLE_COMM_VI_ResetSensor
    for (sns_rst_source_t snsDev = 0; snsDev < SNS_MAX_RST_SOURCE_NUM; snsDev++) {
        s32Ret = ioctl(fd, HI_MIPI_RESET_SENSOR, &snsDev);
        if (HI_SUCCESS != s32Ret) {
            std::cout<<"mipi init: enable sensor clock failed"<<std::endl;
            goto MIPI_INIT;
        }
    }

    // set device attribute  SAMPLE_COMM_VI_SetMipiAttr
    combo_dev_attr_t stcomboDevAttr;
    hi_memcpy(&stcomboDevAttr, sizeof(combo_dev_attr_t),
              &MIPI_4lane_CHN0_SENSOR_IMX334_12BIT_8M_NOWDR_ATTR, sizeof(combo_dev_attr_t));
    stcomboDevAttr.devno = 0;
    stcomboDevAttr.data_rate = MIPI_DATA_RATE_X2;
    s32Ret = ioctl(fd, HI_MIPI_SET_DEV_ATTR, &stcomboDevAttr);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"mipi init: set device attribute failed"<<std::endl;
        goto MIPI_INIT;
    }

    // unreset mipi   SAMPLE_COMM_VI_UnresetMipi
    s32Ret = ioctl(fd, HI_MIPI_UNRESET_MIPI, &devno);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"mipi init: unreset mipi failed"<<std::endl;
        goto MIPI_INIT;
    }

    // unreset sensor  SAMPLE_COMM_VI_UnresetSensor
    for (sns_rst_source_t snsDev = 0; snsDev < SNS_MAX_RST_SOURCE_NUM; snsDev++) {
        s32Ret = ioctl(fd, HI_MIPI_UNRESET_SENSOR, &snsDev);
        if (HI_SUCCESS != s32Ret) {
            std::cout<<"mipi init: unreset sensor failed"<<std::endl;
            goto MIPI_INIT;
        }
    }
    s32Ret = HI_SUCCESS;
MIPI_INIT:
    ::close(fd);
    return s32Ret;
}

int Hi3559VideoCaptureWrap::stopMipi()
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_S32 fd = open(MIPI_DEV_NODE, O_RDWR);
    if (fd < 0) {
        return HI_FAILURE;
    }

    sns_rst_source_t snsDev = 0;
    for (snsDev = 0; snsDev < SNS_MAX_RST_SOURCE_NUM; snsDev++) {
        s32Ret = ioctl(fd, HI_MIPI_RESET_SENSOR, &snsDev);
        if (HI_SUCCESS != s32Ret) {
            break;
        }
    }

    if(s32Ret == HI_SUCCESS) {
        for (snsDev = 0; snsDev < SNS_MAX_CLK_SOURCE_NUM; snsDev++) {
            s32Ret = ioctl(fd, HI_MIPI_DISABLE_SENSOR_CLOCK, &snsDev);
            if (HI_SUCCESS != s32Ret) {
                break;
            }
        }
    }

    if(s32Ret == HI_SUCCESS) {
        combo_dev_t devno = 0;
        s32Ret = ioctl(fd, HI_MIPI_RESET_MIPI, &devno);
        if (HI_SUCCESS != s32Ret) {
            std::cout<<"set mipi reset failed."<<std::endl;
        }
    }

    if(s32Ret == HI_SUCCESS) {
        combo_dev_t devno = 0;
        s32Ret = ioctl(fd, HI_MIPI_DISABLE_MIPI_CLOCK, &devno);
        if (HI_SUCCESS != s32Ret) {
            std::cout<<"disable mipi clock failed."<<std::endl;
        }
    }

    close(fd);
    return s32Ret;
}

int Hi3559VideoCaptureWrap::setVIVPSSWorkMode()
{
    HI_S32 s32Ret = HI_SUCCESS;

    VI_VPSS_MODE_S stVIVPSSMode;
    s32Ret = HI_MPI_SYS_GetVIVPSSMode(&stVIVPSSMode);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_SYS_GetVIVPSSMode failed."<<std::endl;
        return s32Ret;
    }

    stVIVPSSMode.aenMode[0] = VI_PARALLEL_VPSS_PARALLEL;
    s32Ret = HI_MPI_SYS_SetVIVPSSMode(&stVIVPSSMode);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_SYS_SetVIVPSSMode failed."<<std::endl;
        return s32Ret;
    }
    return s32Ret;
}

int Hi3559VideoCaptureWrap::startVI(unsigned int viDev,unsigned int viPipe,unsigned viChn)
{
    HI_S32 s32Ret = HI_SUCCESS;

    // 启动MIPI接口
    if(HI_SUCCESS != startMipi())
        return HI_FAILURE;

    // VI,VPSS模式
    VI_VPSS_MODE_S stVIVPSSMode;
    s32Ret = HI_MPI_SYS_GetVIVPSSMode(&stVIVPSSMode);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_SYS_GetVIVPSSMode failed."<<std::endl;
        return s32Ret;
    }
    stVIVPSSMode.aenMode[0] = VI_PARALLEL_VPSS_PARALLEL;
    s32Ret = HI_MPI_SYS_SetVIVPSSMode(&stVIVPSSMode);
    if (HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_SYS_SetVIVPSSMode failed."<<std::endl;
        return s32Ret;
    }

    // 设置设备属性
    VI_DEV_ATTR_S stDevAttr;
    hi_memcpy(&stDevAttr, sizeof(VI_DEV_ATTR_S), &DEV_ATTR_IMX334_8M_BASE, sizeof(VI_DEV_ATTR_S));
    stDevAttr.stWDRAttr.enWDRMode = WDR_MODE_NONE;
    stDevAttr.enDataRate = DATA_RATE_X2;
    s32Ret = HI_MPI_VI_SetDevAttr(viDev, &stDevAttr);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_SetDevAttr failed."<<std::endl;
        return s32Ret;
    }

    // 使能设备  ---
    s32Ret = HI_MPI_VI_EnableDev(viDev);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_EnableDev failed."<<std::endl;
        return s32Ret;
    }

    // 绑定设备和管道
    VI_DEV_BIND_PIPE_S stDevBindPipe;
    stDevBindPipe.PipeId[0] = viPipe;
    stDevBindPipe.u32Num = 1;
    s32Ret = HI_MPI_VI_SetDevBindPipe(viPipe, &stDevBindPipe);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_SetDevBindPipe failed."<<std::endl;
        goto VI_DEV_ERROR;
    }

    // 创建管道
    VI_PIPE_ATTR_S stPipeAttr;
    hi_memcpy(&stPipeAttr, sizeof(VI_PIPE_ATTR_S), &PIPE_ATTR_3840x2160_RAW12_420_3DNR_RFR, sizeof(VI_PIPE_ATTR_S));
    s32Ret = HI_MPI_VI_CreatePipe(viPipe, &stPipeAttr);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_CreatePipe failed."<<std::endl;
        goto VI_DEV_ERROR;
    }

    // 启动管道
    s32Ret = HI_MPI_VI_StartPipe(viPipe);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_StartPipe failed."<<std::endl;
        goto VI_CHANNEL_ERROR;
    }

    // 设备通道属性
    VI_CHN_ATTR_S stChnAttr;
    hi_memcpy(&stChnAttr, sizeof(VI_CHN_ATTR_S), &CHN_ATTR_3840x2160_420_SDR8_LINEAR, sizeof(VI_CHN_ATTR_S));
    stChnAttr.enDynamicRange = DYNAMIC_RANGE_SDR8;
    stChnAttr.enVideoFormat  = VIDEO_FORMAT_LINEAR;
    stChnAttr.enPixelFormat  = PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    stChnAttr.enCompressMode = COMPRESS_MODE_NONE;
    s32Ret = HI_MPI_VI_SetChnAttr(viPipe,viChn,&stChnAttr);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_SetChnAttr failed."<<std::endl;
        goto Vi_PIPE_ERROR;
    }

    return HI_SUCCESS;

VI_CHANNEL_ERROR:
    HI_MPI_VI_DisableChn(viPipe, viChn);

Vi_PIPE_ERROR:
    HI_MPI_VI_StopPipe(viPipe);
    HI_MPI_VI_DestroyPipe(viPipe);

VI_DEV_ERROR:
    HI_MPI_VI_DisableDev(viChn);

    return HI_FAILURE;
}

int Hi3559VideoCaptureWrap::stopVi(unsigned int viDev,unsigned int viPipe,unsigned viChn)
{
    /**
     *  TODO强制释放VI资源，不考虑调用接口返回值
     */
    if(HI_SUCCESS != stopMipi())
        return HI_FAILURE;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_VI_DisableChn(viPipe, viChn);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_DisableChn failed."<<std::endl;
    }

    s32Ret = HI_MPI_VI_StopPipe(viPipe);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_StopPipe failed."<<std::endl;
    }

    s32Ret = HI_MPI_VI_DestroyPipe(viPipe);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_DestroyPipe failed."<<std::endl;
    }

    s32Ret = HI_MPI_VI_DisableDev(viDev);
    if(HI_SUCCESS != s32Ret) {
        std::cout<<"call HI_MPI_VI_DisableDev failed."<<std::endl;
    }

    return HI_SUCCESS;
}

void Hi3559VideoCaptureWrap::run()
{
    HI_S32 s32Ret;
    s32Ret = HI_MPI_ISP_Run(0);
    if (HI_SUCCESS != s32Ret) {
        printf("HI_MPI_ISP_Run failed with 0x%x.\n", s32Ret);
    }
    std::cout<<"ISP Thread exit."<<std::endl;
}

int Hi3559VideoCaptureWrap::startISP(unsigned int viPipe)
{
    HI_S32 s32Ret = HI_SUCCESS;

    const ISP_SNS_OBJ_S* pstSnsObj = &stSnsImx334Obj;

    ALG_LIB_S stAeLib;
    stAeLib.s32Id = 0;
    strncpy(stAeLib.acLibName, HI_AE_LIB_NAME, sizeof(HI_AE_LIB_NAME));

    ALG_LIB_S stAwbLib;
    stAwbLib.s32Id = 0;
    strncpy(stAwbLib.acLibName, HI_AWB_LIB_NAME, sizeof(HI_AWB_LIB_NAME));

    if (pstSnsObj->pfnRegisterCallback != HI_NULL) {
        s32Ret = pstSnsObj->pfnRegisterCallback(viPipe, &stAeLib, &stAwbLib);
        if (s32Ret != HI_SUCCESS) {
            return s32Ret;
        }
    }

    ISP_SNS_COMMBUS_U uSnsBusInfo;
    uSnsBusInfo.s8I2cDev = 0;
    if (HI_NULL != pstSnsObj->pfnSetBusInfo) {
        s32Ret = pstSnsObj->pfnSetBusInfo(viPipe, uSnsBusInfo);
        if (s32Ret != HI_SUCCESS) {
            return s32Ret;
        }
    }

    HI_MPI_AE_Register(viPipe, &stAeLib);

    HI_MPI_AWB_Register(viPipe, &stAwbLib);

    s32Ret = HI_MPI_ISP_MemInit(viPipe);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_ISP_MemInit failed."<<std::endl;
        return -1;
    }

    ISP_PUB_ATTR_S stPubAttr;
    memcpy(&stPubAttr, &ISP_PUB_ATTR_IMX334_4K_30FPS, sizeof(ISP_PUB_ATTR_S));
    stPubAttr.enWDRMode = WDR_MODE_NONE;
    s32Ret = HI_MPI_ISP_SetPubAttr(viPipe, &stPubAttr);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_ISP_SetPubAttr failed."<<std::endl;
        return s32Ret;
    }

    s32Ret = HI_MPI_ISP_Init(viPipe);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_ISP_Init failed."<<std::endl;
        return s32Ret;
    }

    // 启动ISP线程
    this->start();

    return HI_SUCCESS;
}

int Hi3559VideoCaptureWrap::stopISP(unsigned int viPipe)
{
    HI_S32 s32Ret = HI_FAILURE;

    HI_MPI_ISP_Exit(viPipe);

    // 等待ISP线程退出
    this->join();

    // 注销AWB
    ALG_LIB_S stAwbLib;
    stAwbLib.s32Id = 0;
    strncpy(stAwbLib.acLibName, HI_AWB_LIB_NAME, sizeof(HI_AWB_LIB_NAME));
    HI_MPI_AWB_UnRegister(viPipe, &stAwbLib);

    // 注销AE
    ALG_LIB_S stAeLib;
    stAeLib.s32Id = 0;
    strncpy(stAeLib.acLibName, HI_AE_LIB_NAME, sizeof(HI_AE_LIB_NAME));
    HI_MPI_AE_UnRegister(viPipe, &stAeLib);

    // 注销AE,AWB回调
    const ISP_SNS_OBJ_S* pstSnsObj = &stSnsImx334Obj;
    if (pstSnsObj->pfnUnRegisterCallback != HI_NULL) {

        ALG_LIB_S stAeLib;
        stAeLib.s32Id = 0;
        strncpy(stAeLib.acLibName, HI_AE_LIB_NAME, sizeof(HI_AE_LIB_NAME));

        ALG_LIB_S stAwbLib;
        stAwbLib.s32Id = 0;
        strncpy(stAwbLib.acLibName, HI_AWB_LIB_NAME, sizeof(HI_AWB_LIB_NAME));

        s32Ret = pstSnsObj->pfnUnRegisterCallback(viPipe, &stAeLib, &stAwbLib);
        if (s32Ret != HI_SUCCESS) {
            std::cout<<"call pfnUnRegisterCallback failed."<<std::endl;
        }
    }

    return s32Ret;
}

int Hi3559VideoCaptureWrap::startVPSS(unsigned int vpssGrp,unsigned int vpssChn)
{
    HI_S32 s32Ret;

    VPSS_GRP_ATTR_S stVpssGrpAttr                = {0};
    stVpssGrpAttr.u32MaxW                        = 3840;
    stVpssGrpAttr.u32MaxH                        = 2160;
    stVpssGrpAttr.enPixelFormat                  = PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    stVpssGrpAttr.enDynamicRange                 = DYNAMIC_RANGE_SDR8;
    stVpssGrpAttr.stFrameRate.s32SrcFrameRate    = -1;
    stVpssGrpAttr.stFrameRate.s32DstFrameRate    = -1;
    s32Ret = HI_MPI_VPSS_CreateGrp(vpssGrp, &stVpssGrpAttr);

    VPSS_CHN_ATTR_S stVpssChnAttr;
    stVpssChnAttr.u32Width                    = 3840;
    stVpssChnAttr.u32Height                   = 2160;
    stVpssChnAttr.enChnMode                   = VPSS_CHN_MODE_USER;
    stVpssChnAttr.enCompressMode              = COMPRESS_MODE_NONE;
    stVpssChnAttr.enDynamicRange              = DYNAMIC_RANGE_SDR8;
    stVpssChnAttr.enPixelFormat               = PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    stVpssChnAttr.enVideoFormat               = VIDEO_FORMAT_LINEAR;
    stVpssChnAttr.stFrameRate.s32SrcFrameRate = -1;
    stVpssChnAttr.stFrameRate.s32DstFrameRate = -1;
    stVpssChnAttr.u32Depth                    = 1;
    stVpssChnAttr.bMirror                     = HI_FALSE;
    stVpssChnAttr.bFlip                       = HI_FALSE;
    stVpssChnAttr.stAspectRatio.enMode        = ASPECT_RATIO_NONE;
    s32Ret = HI_MPI_VPSS_SetChnAttr(vpssGrp, vpssChn, &stVpssChnAttr);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_VPSS_SetChnAttr failed."<<std::endl;
    }

    s32Ret = HI_MPI_VPSS_EnableChn(vpssGrp, vpssChn);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_VPSS_EnableChn failed."<<std::endl;
    }

    s32Ret = HI_MPI_VPSS_StartGrp(vpssGrp);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_VPSS_StartGrp failed."<<std::endl;
    }

    return HI_SUCCESS;
}

int Hi3559VideoCaptureWrap::stopVPSS(unsigned int vpssGrp,unsigned int vpssChn)
{
    /**
     *  TODO强制释放VPSS资源，不考虑调用接口返回值
     */
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_VPSS_StopGrp(vpssGrp);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_VPSS_StopGrp failed."<<std::endl;
    }

    s32Ret = HI_MPI_VPSS_DisableChn(vpssGrp, vpssChn);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_VPSS_DisableChn failed."<<std::endl;
    }

    s32Ret = HI_MPI_VPSS_DestroyGrp(vpssGrp);
    if(s32Ret != HI_SUCCESS) {
        std::cout<<"call HI_MPI_VPSS_DestroyGrp failed."<<std::endl;
    }

    return HI_SUCCESS;
}

int Hi3559VideoCaptureWrap::getVideoFrame(unsigned int vpssGrp, unsigned int vpssChn,
        char* buffer,unsigned int bufferLen,unsigned int tWaitTimeout)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VIDEO_FRAME_INFO_S videoFrame;
    HI_S32 s32MilliSec = tWaitTimeout;

    // 开始时间
    // static struct timeval tStartTime;

    // struct timeval tEndTime;
    // gettimeofday(&tEndTime,NULL);

    s32Ret = HI_MPI_VPSS_GetChnFrame(vpssGrp, vpssChn, &videoFrame, s32MilliSec);

    // unsigned int intervalTime = (tEndTime.tv_sec*1000 + tEndTime.tv_usec/1000) -
    //                            (tStartTime.tv_sec*1000 + tStartTime.tv_usec/1000);

    // std::cout<<"-----intervalTime:"<<intervalTime<<std::endl;

    // tStartTime = tEndTime;

    if(HI_SUCCESS == s32Ret) {
#if 0
#if ENABLE_WRITE_FILE
        static FILE *pfd = fopen("./test.yuv", "wb");
#endif
        VIDEO_FRAME_S* pVBuf = &(videoFrame.stVFrame);
        HI_U32 u32Size     = 0;
        HI_U32 u32UvHeight = 0;
        HI_U64 phy_addr;
        // 数据大小,YVU420
        u32Size = (pVBuf->u32Stride[0]) * (pVBuf->u32Height) * 3 / 2;
        u32UvHeight = pVBuf->u32Height / 2;
        phy_addr = pVBuf->u64PhyAddr[0];

        static HI_CHAR* pUserPageAddr[2] = {HI_NULL,HI_NULL};
        pUserPageAddr[0] = (HI_CHAR*) HI_MPI_SYS_Mmap(phy_addr, u32Size);
        if (HI_NULL == pUserPageAddr[0]) {
            return HI_FAILURE;
        }

        char* pVBufVirt_Y = NULL;
        char* pVBufVirt_C = NULL;
        pVBufVirt_Y = pUserPageAddr[0];
        pVBufVirt_C = pVBufVirt_Y + (pVBuf->u32Stride[0]) * (pVBuf->u32Height);

        unsigned int w, h;
        char* pMemContent;
        for (h = 0; h < pVBuf->u32Height; h++) {
            pMemContent = pVBufVirt_Y + h * pVBuf->u32Stride[0];
#if ENABLE_WRITE_FILE
            fwrite(pMemContent, pVBuf->u32Width, 1, pfd);
#endif
        }

        unsigned char TmpBuff[8192] = {0};
        for (h = 0; h < u32UvHeight; h++) {
            pMemContent = pVBufVirt_C + h * pVBuf->u32Stride[1];
            pMemContent += 1;
            for (w = 0; w < pVBuf->u32Width / 2; w++) {
                TmpBuff[w] = *pMemContent;
                pMemContent += 2;
            }
#if ENABLE_WRITE_FILE
            fwrite(TmpBuff, pVBuf->u32Width / 2, 1, pfd);
#endif
        }

        for (h = 0; h < u32UvHeight; h++) {
            pMemContent = pVBufVirt_C + h * pVBuf->u32Stride[1];
            for (w = 0; w < pVBuf->u32Width / 2; w++) {
                TmpBuff[w] = *pMemContent;
                pMemContent += 2;
            }
#if ENABLE_WRITE_FILE
            fwrite(TmpBuff, pVBuf->u32Width / 2, 1, pfd);
#endif
        }
#if ENABLE_WRITE_FILE
        fflush(pfd);
#endif
        HI_MPI_SYS_Munmap(pUserPageAddr[0], u32Size);
        pUserPageAddr[0] = HI_NULL;
#else
        VIDEO_FRAME_S* pVBuf = &(videoFrame.stVFrame);
        HI_U32 u32Size = (pVBuf->u32Stride[0]) * (pVBuf->u32Height) * 3 / 2;
        if(u32Size<bufferLen) {
            static HI_CHAR* pUserPageAddr[2] = {HI_NULL,HI_NULL};
            HI_U64 phy_addr = pVBuf->u64PhyAddr[0];

            pUserPageAddr[0] = (HI_CHAR*) HI_MPI_SYS_Mmap(phy_addr, u32Size);
            if (HI_NULL == pUserPageAddr[0]) {
                return HI_FAILURE;
            }
            char* pVBufVirt = pUserPageAddr[0];
            memcpy(buffer,pVBufVirt,u32Size);
            s32Ret = u32Size;

            HI_MPI_SYS_Munmap(pUserPageAddr[0], u32Size);
            pUserPageAddr[0] = HI_NULL;
        } else {
            s32Ret = HI_FAILURE;
        }
#endif
        HI_MPI_VPSS_ReleaseChnFrame (vpssGrp, vpssChn, &videoFrame);
    } else {
        s32Ret = HI_FAILURE;
        std::cout<<"get frame failed."<<std::endl;
    }
    return s32Ret;
}

