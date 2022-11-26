# coding=UTF-8

import os
import sys
from argparse import ArgumentParser

BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
sys.path.append( BASE_DIR )
from project import project                                                     
from module import module                                                     


# python3 core.py --type project 
# python3 core.py --type module --root_dir ../../DevKits --module_type 1 --module_name QtKit

parser = ArgumentParser()
parser.add_argument('--type', dest='type', type=str, default=['project'], help="gen project or add module to project")    
# Only for Module
parser.add_argument('--root_dir',    dest='root_dir',    type=str, default=['.'], help="project root dir")    
parser.add_argument('--module_type', dest='module_type', type=int, default=[0], help="ModuleType for Kit or Qt")
parser.add_argument('--module_name', dest='module_name', type=str, default=['CCoreKit'], help="kit or App name")
args = parser.parse_args()
  
if __name__ == '__main__':
    if args.type == "project":
        project.Project.create("./config.json")
    elif args.type == "module":
        module.Module.MOUDLE_DIR = "/src-app/"
        module.Module.add(args.root_dir, module.ModuleType(args.module_type), args.module_name)
