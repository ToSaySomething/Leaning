import unittest
import os
import HTMLTestRunner
import datetime

if __name__ == '__main__':    
    suite = unittest.TestLoader().discover(os.path.dirname(os.path.realpath("__file__")))
    d = datetime.datetime.today()
    out_dir = d.strftime("%d-%B-%Y-%H-%M-%S")
    filename = out_dir+'.html'
    if not os.path.exists('../reports/'):
        os.makedirs('../reports/')    
    reports_dir = os.path.join(os.path.join(os.path.dirname("__file__"),os.path.pardir),'reports')
    fp = open(reports_dir+ '/'+ filename,'wb')
    HTMLTestRunner.HTMLTestRunner(stream=fp,title='test report',description='d').run(suite)
    fp.close()