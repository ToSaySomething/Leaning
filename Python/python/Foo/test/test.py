#! /usr/bin/python  
# -*- coding:utf-8 -*-

from pyExcelerator import *
 
w = Workbook() #创建一个工作簿
 
ws = w.add_sheet('Hey, Hades') #创建一个工作表
 
ws.write(0,0,'bit') #在1行1列写入bit

ws.write(0,1,'huang') #在1行2列写入huang
 
ws.write(1,0,'xuan') #在2行1列写入xuan
 
 
 
