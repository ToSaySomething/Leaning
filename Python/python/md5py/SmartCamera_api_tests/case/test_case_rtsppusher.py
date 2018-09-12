import os
from ctypes import *

#获取库版本信息 char*()
def test_RtspPusherGetPushStreamLibVersion(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/rtsppusher/rtsppusher.so"))
    testpy = test.RtspPusherGetPushStreamLibVersion
    #testpy.argtypes = [c_char_p,c_int]                    
    testpy.restype = c_char_p
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],"",'return version sucessful')
    self.assertEqual(data[params],"",'return version error')

#创建推流器 handle()
def test_RtspPusherCreate(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/rtsppusher/rtsppusher.so"))
    testpy = test.RtspPusherCreate
    #testpy.argtypes = [c_char_p,c_int]                    
    testpy.restype = c_handle
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],true,'return PusherCreate Sucessful')
    self.assertEqual(data[params],false,'return PusherCreate error')
   
#启动推流器 int(handle,char*,int,char*,char*,int)
def test_RtspPusherStartStream(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/rtsppusher/rtsppusher.so"))
    testpy = test.RtspPusherStartStream
    testpy.argtypes = [c_handle,c_char_p,c_int,c_char_p,c_char_p,c_int]                    
    testpy.restype = c_int
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return PusherStartStream Sucessful')
    self.assertEqual(data[params],-1,'return PusherStartStream error')

#推送码流 int(handle)
def test_RtspPusherPushFrame(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/rtsppusher/rtsppusher.so"))
    testpy = test.RtspPusherPushFrame
    testpy.argtype = c_handle                 
    testpy.restype = c_int
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return PusherPushFrame Sucessful')
    self.assertEqual(data[params],-1,'return PusherPushFrame error')

#停止码流 int(handle)
def test_RtspPusherStopStream(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/rtsppusher/rtsppusher.so"))
    testpy = test.RtspPusherStopStream
    testpy.argtype = c_handle                 
    testpy.restype = c_int
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return PusherStopStream Sucessful')
    self.assertEqual(data[params],-1,'return PusherStopStream error')

#释放推流资源 int(handle)
def test_RtspPusherRelease(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/rtsppusher/rtsppusher.so"))
    testpy = test.RtspPusherRelease
    testpy.argtype = c_handle                 
    testpy.restype = c_int
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return PusherRelease Sucessful')
    self.assertEqual(data[params],-1,'return PusherRelease error')