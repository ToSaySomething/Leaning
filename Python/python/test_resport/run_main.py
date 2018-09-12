# coding:utf-8

import datetime
import os
import unittest
import HTMLTestRunner
import smtplib

cur_path = os.path.dirname(os.path.realpath(__file__))

#discover add case
def add_case(caseName = "case", rule="test*.py"):
    case_path = os.path.join(cur_path, caseName)

    if not os.path.exists(case_path):os.mkdir(case_path)
    print ("test case path:%s" % case_path)

    discover = unittest.defaultTestLoader.discover(case_path, pattern=rule, top_level_dir=None)

    print (discover)
    return discover

#HTML
def run_case(all_case, reportName = "report"):
    now = time.strftime("%Y_%m_%d_%H_%M_%S")
    report_path = os.path.join(cur_path, reportName)
    if not os.path.exists(report_path):os.mkdir(report_path)
    report_abspath = os.path.join(report_path, now+"resport.html")
    print ("report path:%s" % report_abspath)
    fp = open(report_abspath, "wb")
    runner = HTMLTestRunner.HTMLTestRunner(stream=fp, title=u'test', description=u'run')

    runner.run(all_case)
    fp.close()

def send_mail(send, psw, receiver, smtpserver, report_file, port):
    with open(report_file, "rb")as f:
        mail_body = f.read()
    #context
    msg = MIMEMultipart()
    body = MIMEText(mail_body, subtype = 'html1', _charset = 'utf-8')
    msg['Subject'] = u'autoTest'
    msg['from'] = sender
    msg['to'] = psw

    att = MIMEText(open(report_file,"rb").read(), "base64", "utf-8")
    att

