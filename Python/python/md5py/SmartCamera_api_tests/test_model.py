import os
from ctypes import *
test = cdll.LoadLibrary(os.path.join(os.getcwd(), "librtsppusher.so"))
print test
testpy = test.RTSP_Pusher_StartStream          #loadFile是C++函数
testpy.argtype = c_char_p                      #这里是testy.argtype而不是testy.argtypes,参数多与两个才用argtypes：encodeFile.argtypes = [c_char_p, c_char_p]
testpy.restype = c_char_p
ss = "/systemInfo.sys"      #向 loadFile传的参数
params = testpy(ss)
print params