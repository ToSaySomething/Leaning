import os
from ctypes import *

#获取库版本信息 int(char*, int)
def test_cwGetVideoCaptureVersion_successful(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/videocature/videocature.so"))
    print test
    testpy = test.cwGetVideoCaptureVersion
    #这里是testpy.argtype而不是testpy.argtypes,
    #参数多与两个才用argtypes：encodeFile.argtypes = [c_char_p, c_char_p]
    testpy.argtypes = [c_char_p,c_int]                    
    testpy.restype = c_int
    ss = "/systemInfo.sys"      #传参
    params = testpy(ss)
    print params
    self.assertnotEqual(data[params],-1,'return version lens')

def test_cwGetVideoCaptureVersion_error(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/videocature/videocature.so"))
    testpy = test.cwGetVideoCaptureVersion
    testpy.argtypes = [c_char_p,c_int]                    
    testpy.restype = c_int
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertEqual(data[params],-1,'return version error')

# 设置视频捕捉函数 void(func)  
def test_cwSetVideoCaptureCallBack(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/videocature/videocature.so"))
    testpy = test.cwSetVideoCaptureCallBack
    testpy.argtype = c_func              
    testpy.restype = c_void
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],true,'return SetVideoCaptureCallBack successful')
    self.assertEqual(data[params],false,'return SetVideoCaptureCallBack error')

# 打开视频设备 handle(char*, int[enum], int)
def test_cwOpenVideoDevice(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/videocature/videocature.so"))
    testpy = test.cwOpenVideoDevice
    testpy.argtypes = [c_char_p, c_int, c_int]              
    testpy.restype = c_handle
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],true,'return OpenVideoDevice successful')
    self.assertEqual(data[params],false,'return OpenVideoDevice error')

#  关闭视频设备 int(handle)
def test_ cwCloseVideoDevice(self):
    test = cdll.LoadLibrary(os.path.join(os.getcwd(), "CPlusDynLib/videocature/videocature.so"))
    testpy = test. cwCloseVideoDevice
    testpy.argtype = c_handle             
    testpy.restype = c_int
    ss = "/systemInfo.sys"    #传参
    params = testpy(ss)
    self.assertnotEqual(data[params],true,'return CloseVideoDevice successful')
    self.assertEqual(data[params],false,'return CloseVideoDevice error')