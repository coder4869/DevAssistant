# coding=UTF-8

import os
import sys
import enum

MODULE_BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
CORE_BASE_DIR   = os.path.dirname(MODULE_BASE_DIR)
sys.path.append( CORE_BASE_DIR )
from pytool import pyt_file 

MODULE_TEMPLATE_CMAKE = MODULE_BASE_DIR + "/template/cmake/"
MODULE_TEMPLATE_CODE  = MODULE_BASE_DIR + "/template/code/"

MODULE_CMAKE_APPEND_NORM="""

# MODULE_NAME
if(MODULE_NAME)
    set(MODULE_NAME_SRC)
    include(${SRC_ROOT}/MODULE_NAME/MODULE_NAME.cmake)
    set(SRC_FILES ${SRC_FILES} ${MODULE_NAME_SRC})
endif(MODULE_NAME)

"""

MODULE_CMAKE_APPEND_QT="""

# MODULE_NAME
if(WITH_QT AND MODULE_NAME)
    set(MODULE_NAME_SRC)
    include(${SRC_ROOT}/MODULE_NAME/MODULE_NAME.cmake)
    set(SRC_FILES ${SRC_FILES} ${MODULE_NAME_SRC})
endif(WITH_QT AND MODULE_NAME)

"""


MODULE_CMAKE_APPEND_LIB="""

# MODULE_NAME
if(MODULE_NAME)
    set(MODULE_NAME_INC)
    set(MODULE_NAME_LIB)
    include(${SRC_ROOT}/MODULE_NAME/MODULE_NAME.cmake)
    set(THIRD_PARTY_INC ${THIRD_PARTY_INC} ${MODULE_NAME_INC})
    set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${MODULE_NAME_LIB})
endif(MODULE_NAME)

"""

class ModuleType(enum.Enum):
    Norm  = 0
    Qt    = 1
    Lib   = 2

class Module(object):
    ROOT_DIR = CORE_BASE_DIR
    MOUDLE_DIR = "/src/" # init required
    MOUDLE_ABS_DIR = CORE_BASE_DIR + MOUDLE_DIR

    @staticmethod
    def add(root_dir:str, module_type:ModuleType, module_name:str, has_main:bool):
        print("root_dir =", root_dir, "module_type =", module_type, "module_name =", module_name)
        Module.ROOT_DIR = root_dir
        Module.MOUDLE_ABS_DIR = root_dir + Module.MOUDLE_DIR

        if ModuleType(module_type) is ModuleType.Norm:
            Module.add_norm_module(module_name, has_main)
        elif ModuleType(module_type) is ModuleType.Qt:
            Module.add_qt_module(module_name, has_main)
        elif ModuleType(module_type) is ModuleType.Lib:
            Module.add_lib_module(module_name)
        else:
            print("Invalid ModuleType ", module_type)
            for name, value in ModuleType.__members__.items():
                print(name, value)

    @staticmethod
    def add_norm_module(name:str, has_main:bool):
        dst_dir = Module.MOUDLE_ABS_DIR + name
        print("add_norm_module() dst_dir=", dst_dir)
        if Module.check_path(dst_dir):
            Module.add_module_to_project(MODULE_CMAKE_APPEND_NORM, name)
            Module.add_module_cmake(dst_dir, name, "norm.cmake")
            if has_main:
                Module.add_module_main(dst_dir, "main.cpp.NORM")
            else:
                Module.add_module_header(dst_dir, name)
            return True
        return False

    @staticmethod
    def add_qt_module(name:str, has_main:bool):
        dst_dir = Module.MOUDLE_ABS_DIR + name
        print("add_qt_module() dst_dir=", dst_dir)
        if Module.check_path(dst_dir):
            Module.add_module_to_project(MODULE_CMAKE_APPEND_QT, name)
            Module.add_module_cmake(dst_dir, name, "qt.cmake")
            if has_main:
                Module.add_module_main(dst_dir, "main.cpp.QT")
            else:
                Module.add_module_header(dst_dir, name)
            os.makedirs(dst_dir + "/Forms")
            os.makedirs(dst_dir + "/Res")
            return True
        return False

    @staticmethod
    def add_lib_module(name:str):
        dst_dir = Module.MOUDLE_ABS_DIR + name
        print("add_lib_module() dst_dir=", dst_dir)
        if Module.check_path(dst_dir):
            Module.add_module_to_project(MODULE_CMAKE_APPEND_LIB, name)
            Module.add_module_cmake(dst_dir, name, "lib.cmake")
            return True
        return False

    @staticmethod
    def add_module_cmake(dst_dir:str, name:str, cmake:str):
        dst_cmake = dst_dir + "/" + name + ".cmake"
        pyt_file.File.copy_to_file(MODULE_TEMPLATE_CMAKE + cmake, dst_cmake)
        pyt_file.File.replace_string(dst_cmake, "MODULE_NAME", name)

    @staticmethod
    def add_module_header(dst_dir, name):
        dst_header = dst_dir + "/" + name + ".h"
        pyt_file.File.copy_to_file(MODULE_TEMPLATE_CODE + "MODULE_NAME.h", dst_header)
        pyt_file.File.replace_string(dst_header, "MODULE_NAME", name.upper())

    @staticmethod
    def add_module_main(dst_dir:str, main:str):
        dst_main = dst_dir + "/main.cpp"
        pyt_file.File.copy_to_file(MODULE_TEMPLATE_CODE + main, dst_main)

    @staticmethod
    def add_module_to_project(append_str, name):
        dir_name = os.path.basename(os.path.normpath(Module.MOUDLE_ABS_DIR))
        dir_cmake = Module.MOUDLE_ABS_DIR + dir_name + ".cmake"
        print("dir_cmake=",dir_cmake)
        pyt_file.File.append_string(dir_cmake, append_str)
        pyt_file.File.replace_string(dir_cmake, "MODULE_NAME", name)

    @staticmethod
    def check_path(path):
        path=path.strip()       # remove space
        path=path.rstrip("\\")  # remove tail \\
        if os.path.exists(path):
            print("path=%s 目录已存在，请备份后删除目录，或者变更目标目录"%(path))
            return False
        os.makedirs(path) 
        print("path=%s 创建成功"%(path))
        return True
