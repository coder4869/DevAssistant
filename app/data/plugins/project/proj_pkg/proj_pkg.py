# coding=UTF-8
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

import os
import sys

PROJECT_BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
PYTOOL_DIR   = os.path.dirname( os.path.dirname(PROJECT_BASE_DIR) )
sys.path.append( PYTOOL_DIR )
from pytool import pyt_file
from pytool import pyt_json

PROJECT_PKG_WIN_DIR = PROJECT_BASE_DIR + "/pkg-win"
PROJECT_PKG_RPM_DIR = PROJECT_BASE_DIR + "/pkg-rpm"
PKG_WIN_NSIS        = "/pkg-win-nsis.bat"
PKG_WIN_NSIS_PATH   = "/pkg-win/pkg-win-nsis.bat"
PKG_RPM             = "/pkg-rpm.sh"
PKG_RPM_PATH        = "/pkg-rpm/pkg-rpm.sh"

class ProjPkg(object):
    GROUP_LIST:list = []

    @staticmethod
    def pkg(json_config):
        dic = pyt_json.PytJson.load_config(json_config)
        if not dic:
            return None
        proj_name   = dic["proj_name"]
        root_dir    = dic["root_dir"]
        script_dir  = dic["script_dir"]
        pkg_dirs    = dic["pkg_dirs"]
        # pkg_version = dic["pkg_version"]
        # pkg_arch    = dic["pkg_arch"]

        if not os.path.exists(root_dir):
            print("root—dir not exist: " + root_dir)
            return
        
        ProjPkg.add_pkg_scripts(proj_name, root_dir, script_dir)
        ProjPkg.update_pkg_dirs(root_dir, script_dir, pkg_dirs)

    @staticmethod
    def add_pkg_scripts(proj_name:str, root_dir:str, scripts_dir:str):
        script_abs_dir = root_dir + "/" + scripts_dir

        # prapare ${scripts_dir}/pkg-win
        pkg_win_dir = script_abs_dir + "/pkg-win" 
        pyt_file.File.copy_dir(PROJECT_PKG_WIN_DIR, pkg_win_dir )
        pkglist = os.listdir(pkg_win_dir)
        for fitem in pkglist:
            file = pkg_win_dir + "/" + fitem
            print(file)
            if os.path.isfile(file) and file.endswith("bat"):
                pyt_file.File.replace_string(file, "_PROJ_NAME_", proj_name) # Set ${PROJECT_NAME}
        pyt_file.File.copy_to_file(script_abs_dir + PKG_WIN_NSIS_PATH, root_dir + PKG_WIN_NSIS)
        os.remove(script_abs_dir + PKG_WIN_NSIS_PATH)

        # prapare ${scripts_dir}/pkg-rpm
        pkg_rpm_dir = script_abs_dir + "/pkg-rpm" 
        pyt_file.File.copy_dir(PROJECT_PKG_RPM_DIR, pkg_rpm_dir)
        pkglist = os.listdir(pkg_rpm_dir)
        for fitem in pkglist:
            file = pkg_rpm_dir + "/" + fitem
            print(file)
            if os.path.isfile(file):
                pyt_file.File.replace_string(file, "_PROJ_NAME_", proj_name) # Set ${PROJECT_NAME}
            elif os.path.isdir(file):
                sublist = os.listdir(file)
                for it in pkglist:
                    subfile = file + "/" + it
                    print(subfile)
                    if os.path.isfile(subfile):
                        pyt_file.File.replace_string(subfile, "_PROJ_NAME_", proj_name) # Set ${PROJECT_NAME}
        pyt_file.File.copy_to_file(script_abs_dir + PKG_RPM_PATH, root_dir + PKG_RPM)
        os.remove(script_abs_dir + PKG_RPM_PATH)

    @staticmethod
    def update_pkg_dirs(root_dir:str, scripts_dir:str, pkg_dirs:list):
        script_abs_dir = root_dir + "/" + scripts_dir
        # TODO::update pkg dirs
        for it in pkg_dirs:
            print("add_pkg_dirs: " + it)
