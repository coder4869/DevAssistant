# coding=UTF-8
# MIT License
# 
# Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import shutil

class File(object):

    @staticmethod
    def copy_dir(src_dir, dst_dir):
        if not os.path.exists(src_dir):
            return False
        if not os.path.exists(dst_dir):
            os.makedirs(dst_dir)
        dlist = os.listdir(src_dir)
        for f in dlist:
            src_file = os.path.join(src_dir, f)
            dst_file = os.path.join(dst_dir, f)
            if os.path.isfile(src_file):
                shutil.copyfile(src_file, dst_file)
            if os.path.isdir(src_file):
                File.copy_dir(src_file, dst_file)
        return True

    @staticmethod 
    def copy_to_dir(src_file, dst_dir):
        if not os.path.isfile(src_file):
            print("%s not exist!"%(src_file))
            return False
        else:
            fpath, fname = os.path.split(src_file)  # split file name && path
            dst_file = dst_dir + "/" + fname

            if os.path.isfile(dst_file):
                print("dst path %s exist"%(dst_file))
                return False

            if not os.path.exists(dst_dir):
                os.makedirs(dst_dir)
            shutil.copy(src_file, dst_file)         # copy file
            print("copy %s -> %s"%(src_file, dst_file))
            return True
        
    @staticmethod 
    def copy_to_file(src_file, dst_file):
        if not os.path.isfile(src_file):
            print("%s not exist!"%(src_file))
            return False
        
        elif os.path.exists(dst_file):
            print("dst path %s exist"%(dst_file))
            return False

        else:
            fpath, fname = os.path.split(dst_file)  # split file name && path
            if not os.path.exists(fpath):
                os.makedirs(fpath)
            shutil.copy(src_file, dst_file)         # copy file
            print("copy %s -> %s"%(src_file, dst_file))
            return True

    @staticmethod
    def replace_string(file_path, old_str, new_str):
    # https://blog.csdn.net/u012206617/article/details/121673782
        if os.path.exists(file_path):
            file_data = ""
            with open(file_path, "r", encoding="utf-8") as f: 
                for line in f:
                    if old_str in line:
                        line = line.replace(old_str, new_str)
                    file_data += line
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(file_data)
            return True
        return False
    
    @staticmethod
    def append_string(file_path, data):
        if os.path.exists(file_path):
            with open(file_path, "a", encoding="utf-8") as f:
                f.write(data)
            return True
        return False