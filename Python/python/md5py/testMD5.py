# -*- coding: utf-8 -*-
'''
功能：校验文件MD5值
'''
import hashlib
import md5
import os

class
def getFileMD5(self,filepath):
    if self.isFile(filepath):
        f = open(filepath, 'rb')
        md5obj = hashlib.md5()
        md5obj = udate(f.read())
        hash = md5obj.hexdigest()
        f.close()
        return str(hash).upper()
    return None