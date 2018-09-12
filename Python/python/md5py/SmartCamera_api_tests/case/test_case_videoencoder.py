import os
from ctypes import *

#创建编码器 handle(int)
def test_cwCreateEncoder(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "videoencoder.so"))
    testpy = test.cwCreateEncoder
    testpy.argtype = c_int
    testpy.restype = c_handle
    ss = "/systemInfo.sys"      #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return Create successful')
    self.assertEqual(data[params],-1,'return Create error')

# 编码一帧数据 handle(handle,char*,int,char*,int)
def test_cwEncoderOneFrame(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "videoencoder.so"))
    testpy = test.cwEncoderOneFrame
    testpy.argtypes = [c_handle,c_char_p,c_int,c_char_p,c_int]
    testpy.restype = c_handle
    ss = "/systemInfo.sys"      #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return Encoder successful')
    self.assertEqual(data[params],-1,'return Encoder error')

# 销毁编码器 handle(handle,char*,int,char*,int)
def test_cwDestroyEncoder(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "videoencoder.so"))
    testpy = test.cwDestroyEncoder
    testpy.argtype = c_handle
    testpy.restype = c_int
    ss = "/systemInfo.sys"      #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],-1,'return Destroy successful')
    self.assertEqual(data[params],-1,'return Destroy error')