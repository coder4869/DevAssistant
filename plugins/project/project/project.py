# coding=UTF-8
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

import os
import sys

PROJECT_BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
PYTOOL_DIR   = os.path.dirname( os.path.dirname(PROJECT_BASE_DIR) )
sys.path.append( PYTOOL_DIR )
from pytool import pyt_file                                                     
from pytool import pyt_json                                                    
from module import module   

PROJECT_BUILD_DIR   = PROJECT_BASE_DIR + "/build"
PROJECT_CMAKE_DIR   = PROJECT_BASE_DIR + "/cmake"
MODULE_TEMPLATE_DIR = PROJECT_BASE_DIR + "/template"

OPTION_STR_SIZE:int = 20
OPTION_TEMPLATE:str = "# option(MODULE_OPTION  \"Build with MODULE_OPTION\" ON)"

MODULE_LIB_DEPS = """
if(MODULE_NAME)
    add_dependencies(${PROJECT_NAME} MODULE_NAME)
    target_link_libraries(${PROJECT_NAME} PUBLIC MODULE_NAME)
endif(MODULE_NAME)
"""

MODULE_LIB_DEPS_QT = """
if(WITH_QT AND MODULE_NAME)
    add_dependencies(${PROJECT_NAME} MODULE_NAME)
    target_link_libraries(${PROJECT_NAME} PUBLIC MODULE_NAME)
endif(MODULE_NAME)
"""

class Project(object):
    GROUP_LIST:list = []

    @staticmethod
    def create(json_config):
        dic = pyt_json.PytJson.load_config(json_config)
        if not dic:
            return None
        proj_name = dic["proj_name"]
        dir_root  = dic["dir_proj"]
        # Create Project Dir
        if not os.path.exists(dir_root):
            os.makedirs(dir_root)
        # Init dir_help Dirs and Add project.json
        Project.add_help_dirs(dir_root, dic["dir_help"], proj_name)   
        pyt_file.File.copy_to_file(json_config, dir_root + "/" + dic["dir_help"]["conf"] + "/project.json")
        if "options" in dic.keys():
            Project.add_options(dir_root, dic["options"])
        # Init dir_codes and Add ${INC_GROUP}
        Project.init_codes_dir(dir_root, dic["dir_codes"])
        Project.add_group_inc(dir_root)

    @staticmethod
    def add_help_dirs(root_dir:str, help_dirs:list, proj_name:str):
        for k in help_dirs.keys():
            help_dir = root_dir + "/" + help_dirs[k]
            if not os.path.exists(help_dir):
                os.makedirs(help_dir)
            if k.lower() == "scripts":
                Project.add_scripts_dir(root_dir, help_dirs[k], proj_name)

    @staticmethod
    def add_scripts_dir(root_dir:str, scripts_dir:str, proj_name:str):
        script_abs_dir = root_dir + "/" + scripts_dir
        # prapare ${PROJECT}/CMakeLists
        pyt_file.File.copy_to_file(MODULE_TEMPLATE_DIR + "/CMakeLists.txt.PROJ", root_dir + "/CMakeLists.txt")
        # prapare ${scripts_dir}/cmake
        pyt_file.File.copy_dir(PROJECT_CMAKE_DIR, script_abs_dir + "/cmake" )
        # prepare ${PROJECT}/*.sh *.bat
        pyt_file.File.copy_dir(PROJECT_BUILD_DIR, root_dir + "/")

        flist = os.listdir(PROJECT_BUILD_DIR)
        for fitem in flist:
            file = root_dir + "/" + fitem
            if not os.path.isdir(fitem):
                pyt_file.File.replace_string(file, "_PROJ_NAME_", proj_name) # Set ${PROJECT_NAME}
        
    @staticmethod
    def add_options(root_dir:str,  options:object):
        for opt in options.keys():
            name = opt[5:] # remove WITH_
            to_string = "option(" + opt.ljust(OPTION_STR_SIZE,' ') + "\"Build with " + name.ljust(OPTION_STR_SIZE,' ') + "\"\t" + options[opt] + ")"
            to_string = to_string + "\n" + OPTION_TEMPLATE
            pyt_file.File.replace_string(root_dir + "/CMakeLists.txt", OPTION_TEMPLATE, to_string)

    @staticmethod
    def init_codes_dir(root_dir:str, codes_dirs:list):
        for group in codes_dirs:
            # add module groups
            gtype = group["group"]
            group_dir = group["group_dir"]
            Project.GROUP_LIST.append(group_dir)
            Project.add_module_group(root_dir, group_dir, gtype)
            # add child modules
            modules = group["modules"]
            for item in modules:
                Project.add_module(root_dir, group_dir, gtype, item)
    
    @staticmethod 
    def add_group_inc(root_dir:str):
        inc_group:str = "set(INC_GROUP "
        for group_dir in Project.GROUP_LIST:
            inc_group = inc_group + " ${PROJ_ROOT}" + group_dir
        inc_group = inc_group + ")" 
        pyt_file.File.replace_string(root_dir + "/CMakeLists.txt", "# set(INC_GROUP)", inc_group)

    @staticmethod
    def add_module_group(root_dir:str, group_dir:str, gtype:str):
        group_abs_dir = root_dir + group_dir 
        if not os.path.exists(group_abs_dir):
            os.makedirs(group_abs_dir)
        # copy src.cmake.GROUP to group_dir
        dir_name = os.path.basename(os.path.normpath(group_abs_dir))
        cmake_path = group_abs_dir +  "/" + dir_name + ".cmake"
        if gtype.lower() == "lib":
            pyt_file.File.copy_to_file(MODULE_TEMPLATE_DIR + "/deps.cmake", cmake_path)
        else:
            pyt_file.File.copy_to_file(MODULE_TEMPLATE_DIR + "/src.cmake.GROUP", cmake_path)
        # Add Group cmake-include to ${PROJECT}/CMakeLists.txt
        from_srting = "# include(Module-Group.cmake)"
        to_string = "include(${PROJ_ROOT}" + group_dir + "/" + dir_name + ".cmake)"
        if pyt_file.File.has_string(root_dir + "/CMakeLists.txt", to_string):
            return

        to_string = from_srting + "\n" + to_string
        # Add Extra Info For Third-Party cmake
        if gtype.lower() == "lib":
            to_string = to_string + "\n" + "set(INC_GROUP ${THIRD_PARTY_INC} ${INC_GROUP})"
        pyt_file.File.replace_string(root_dir + "/CMakeLists.txt", from_srting, to_string)

    @staticmethod
    def add_module(root_dir:str, group_dir:str, gtype:str, obj:object):
        # Add Module option to ${PROJECT}/CMakeLists.txt
        name = obj["module"]
        Project.add_module_option(root_dir, obj)
        
        # add Module
        mtype = module.Module.TYPE_MAP[gtype.lower()]
        deps:list = obj["deps"] if "deps" in obj else []                # get deps
        module.Module.IS_LIB_DEPS = True if "gen_lib" in obj else False # is gen_lib
        module.Module.MOUDLE_DIR = group_dir + "/"
        module.Module.add(root_dir, mtype, name, deps)
        # add Module deps to ${PROJECT}/CMakeLists.txt
        # Project.add_module_lib_deps(root_dir, gtype, obj)
    
    @staticmethod
    def add_module_option(root_dir:str, obj:object):
        name = obj["module"]
        option = obj["option"]
        to_string = "option(" + name.ljust(OPTION_STR_SIZE,' ') + "\"Build with " + name.ljust(OPTION_STR_SIZE,' ') + "\"\t" + option + ")"
        to_string = to_string + "\n" + OPTION_TEMPLATE
        pyt_file.File.replace_string(root_dir + "/CMakeLists.txt", OPTION_TEMPLATE, to_string)
    
    @staticmethod
    def add_module_lib_deps(root_dir:str, gtype:str, obj:object):
        module.Module.IS_LIB_DEPS = False
        for k in obj.keys():
            if k == "gen_lib":
                name = obj["module"]
                gen_lib = obj["gen_lib"]
                cmake_path = root_dir + "/CMakeLists.txt"
                if gen_lib.lower() == "yes":
                    module.Module.IS_LIB_DEPS = True
                    if gtype.lower().startswith("qt"):
                        pyt_file.File.append_string(cmake_path, MODULE_LIB_DEPS_QT)
                        pyt_file.File.replace_string(cmake_path, "MODULE_NAME", name)
                    elif not gtype.lower() == "lib":
                        pyt_file.File.append_string(cmake_path, MODULE_LIB_DEPS)
                        pyt_file.File.replace_string(cmake_path, "MODULE_NAME", name)