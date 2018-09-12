# coding:utf-8
import unittest
import os
import HTMLTestRunner_jpg

# python2.7要是报编码问题，就加这三行，python3不用加
import sys
reload(sys)
sys.setdefaultencoding('utf8')

cur_path = os.path.dirname(os.path.realpath(__file__))
case_path = os.path.join(cur_path, "case")        # 测试用例的路径
report_path = os.path.join(cur_path, "report")  # 报告存放路径

if __name__ == "__main__":
    discover = unittest.defaultTestLoader.discover(case_path,"test*.py")
    print(discover)
    run = HTMLTestRunner_jpg.HTMLTestRunner(title="可以装逼的测试报告",
                                            description="测试用例参考",
                                            stream=open(report_path+"\\result.html", "wb"),
                                            retry=1)

    run.run(discover)