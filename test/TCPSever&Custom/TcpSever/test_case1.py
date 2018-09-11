import os,unittest
from ctypes import *

class TestIsflag(unittest.TestCase):
    def test_isflag(self):
        test = cdll.LoadLibrary(os.path.join(os.getcwd(), "/home/deng/Workspace/test/TcpSever/build-TcpServer-Desktop_Qt_5_11_1_GCC_64bit-Debug/libTcpServer.so"))
        print test
        testpy = test.isflag 
        #testpy.argtype = c_void_p
        testpy.restype = c_int
        ss = "/systemInfo.sys"
        params = testpy()
        print params
        self.assertEqual(params,-1,'sucessful')

if __name__ == '__main__':
    suite = unittest.TestSuite()

    tests = [TestIsflag("test_isflag")]
    suite.addTests(tests)

    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(suite)
