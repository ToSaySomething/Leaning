#! /usr/bin/python  
# encoding:utf-8  
  
import sys
from pyExcelerator import *  

def read_txt(fpath):
	cpu = []
	memory_used = []
	time = []
	date = []
	f = open(fpath,'r')
	lines = f.readlines()
	for line in lines:	
		if 'Current date' in line:
			date_temp = line.split(':')			
			date.append(date_temp[1].strip())	

		if 'load average' in line:
			time_temp = line.split(',')
			time_m = time_temp[0].split()
			time.append(time_m[2])	
		""" # 获取cpu , memory
		if '%Cpu(s)' in line:
			cpu_temp = line.split(',')
			cpu_m = cpu_temp[0].split(':')
			cpu.append(cpu_m[1].split()[0]) """

		# 获取cpu , memory
		if 'SmartCamera' in line:
			if 'SmartCamera-RTS' not in line:
				cpu_temp = line.strip().split()				
				cpu.append(cpu_temp[8])

		if 'KiB Mem' in line:
			mem_temp = line.split(',')
			mem_m = mem_temp[2].split()
			memory_used.append(mem_m[0])
	f.close()
	return date,cpu,memory_used,time

def write_to_excel(fpath,date,time,cpu,memory_used): 
	w = Workbook()    
	ws = w.add_sheet('Sheet1')
	ws.write(0, 1, 'date_time')
	ws.write(0, 3, 'cpu_us') 
	ws.write(0, 5, 'memory_used')  
		
	for i in range(len(cpu)):
		ws.write(i + 1, 1, date[i] + '_' + time[i]) 
		ws.write(i + 1, 3, float(cpu[i])/4) 
		temp = int(memory_used[i])/1024
		ws.write(i + 1, 5, float(temp))  		
   
	fpath_excel=fpath.replace('txt','xls')  
	w.save(fpath_excel)  

""" fpath = ['D:/caroline/python_scripts/top_20180705100216_237.txt',
		 'D:/caroline/python_scripts/top_20180705100222_238.txt',
		 'D:/caroline/python_scripts/top_20180705100252_234.txt',
		 'D:/caroline/python_scripts/top_20180705100245_163.txt' ] """
fpath = ['D:/caroline/python_scripts/top_20180704104452.txt']		 

for i in range(len(fpath)):
	[date,cpu,memory_used,time] = read_txt(fpath[i])	
	write_to_excel(fpath[i],date,time,cpu,memory_used)  