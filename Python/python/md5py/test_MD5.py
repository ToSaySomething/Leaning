# -*- coding: utf-8 -*-
import hashlib
import os
import datetime

def GetFileMd5(filename):
    if not os.path.isfile(filename):
        return
    myhash = hashlib.md5()
    f = file(filename,'rb')
    while True:
        b = f.read(8096)
        if not b :
            break
        myhash.update(b)
    f.close()
    hash = myhash.hexdigest()
    return str(hash).lower()

#filepath = "e:\SmartCamera-full-1.0.2.20180623.tar.bz2"
filepath = raw_input("path:").strip()

#output MD5
re_str = GetFileMd5(filepath)
print re_str
file_name = os.path.basename(filepath) + ".md5.txt"
print file_name + " is exists"

with open(file_name,"w") as ff:
        ff.write(re_str)