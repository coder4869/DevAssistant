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
import sys
from argparse import ArgumentParser

BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
PYTOOL_DIR = os.path.dirname( BASE_DIR )
sys.path.append( PYTOOL_DIR )

from project import project                                                     
from module import module                                                     

# python3 run.py --type project 
# python3 run.py --type module --root_dir ../../DevKits --module_type 1 --module_name QtKit

parser = ArgumentParser()
parser.add_argument('--type', dest='type', type=str, default=['project'], help="gen project or add module to project")    
# Only for Module
parser.add_argument('--root_dir',    dest='root_dir',    type=str, default=['.'], help="project root dir")    
parser.add_argument('--module_type', dest='module_type', type=int, default=[0], help="ModuleType for Kit or Qt")
parser.add_argument('--module_name', dest='module_name', type=str, default=['CCoreKit'], help="kit or App name")
args = parser.parse_args()
  
if __name__ == '__main__':
    if args.type == "project":
        project.Project.create(BASE_DIR + "/project.json")
    elif args.type == "module":
        module.Module.MOUDLE_DIR = "/src-app/"
        module.Module.add(args.root_dir, module.ModuleType(args.module_type), args.module_name, has_main=True, deps=[])
