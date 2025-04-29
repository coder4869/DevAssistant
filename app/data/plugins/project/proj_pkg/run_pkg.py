# coding=UTF-8
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

import os
import sys
from argparse import ArgumentParser

PROJECT_BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
PYTOOL_DIR   = os.path.dirname( os.path.dirname(PROJECT_BASE_DIR) )
sys.path.append( PYTOOL_DIR )

import proj_pkg                                                     

# python run_pkg.py --config ../pkg.json.bak
# root_dir
#   |- bin64
#   |- conf
#   |- data
#       |- resources
#       |- ...
#   |_ scripts(_SCRIPT_DIR_)
# pkg.json:
# { 
#     "proj_name":"_PROJ_NAME_", 
#     "root_dir":"_ROOT_DIR_", 
#     "script_dir":"_SCRIPT_DIR_",
#     "pkg_dirs":["bin64", "conf", "data", "tools"] 
# }
parser = ArgumentParser()
parser.add_argument('--config', dest='config', type=str, default=PROJECT_BASE_DIR + "/pkg.json", help="app binary pkg.json")
args = parser.parse_args()
  
if __name__ == '__main__':
    print("json = ", args.config)
    proj_pkg.ProjPkg.pkg_gen(args.config)
    proj_pkg.ProjPkg.pkg_run(args.config)