import sys
import unittest
import os
import HTMLTestRunnerDIY
import datetime
import yagmail


allcase='/home/deng/Workspace/swig/test_c_so/TcpSever/TcpSever/test_case'     #指明要自动查找的py文件所在文件夹路径
if __name__ == '__main__':    
    #suite = unittest.TestLoader().discover(os.path.dirname(os.path.realpath("__file__")))
    suite = unittest.defaultTestLoader.discover(allcase, "test_case.py", top_level_dir = None)
    print suite??
    d = datetime.datetime.today()
    out_dir = d.strftime("%d-%B-%Y-%H-%M-%S")
    filename = out_dir + '.html'
    if not os.path.exists('../reports/'):
        os.makedirs('../reports/')    
    reports_dir = os.path.join(os.path.join(os.path.dirname("__file__"),os.path.pardir),'reports')
    fp = open(reports_dir+ '/'+ filename,'wb')
    #html
    HTMLTestRunnerDIY.HTMLTestRunner(stream=fp,title='test report',description='follow').run(suite)
    fp.close()