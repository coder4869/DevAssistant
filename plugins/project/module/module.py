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
import enum

MODULE_BASE_DIR = os.path.dirname( os.path.abspath(__file__) )
PYTOOL_DIR   = os.path.dirname( os.path.dirname(MODULE_BASE_DIR) )
sys.path.append( PYTOOL_DIR )
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

MODULE_CMAKE_APPEND_LIB_DEPS_NORM="""
# MODULE_NAME
if(MODULE_NAME)
    include(${SRC_ROOT}/MODULE_NAME/MODULE_NAME.cmake)
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

MODULE_CMAKE_APPEND_LIB_DEPS_QT="""
# MODULE_NAME
if(WITH_QT AND MODULE_NAME)
    include(${SRC_ROOT}/MODULE_NAME/MODULE_NAME.cmake)
endif(WITH_QT AND MODULE_NAME)
"""

MODULE_CMAKE_APPEND_LIB_THRID_PARTY="""
# MODULE_NAME
if(MODULE_NAME)
    set(MODULE_NAME_INC)
    set(MODULE_NAME_LIB)
    include(${SRC_ROOT}/MODULE_NAME/MODULE_NAME.cmake)
    set(THIRD_PARTY_INC ${THIRD_PARTY_INC} ${MODULE_NAME_INC})
    set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${MODULE_NAME_LIB})
endif(MODULE_NAME)
"""

MODULE_CMAKE_APPEND_LIB_DEPS="""
if(MODULE_NAME)
    add_dependencies(${LIB_NAME} MODULE_NAME)
else()
    message(FATAL_ERROR "option ON for MODULE_NAME is required !")
endif(MODULE_NAME)
"""

class ModuleType(enum.Enum):
    APP     = 0
    QtAPP   = 1
    Lib     = 2
    LibQt   = 3
    LibDeps = 4

class Module(object):
    ROOT_DIR = "."        # private, parent 
    MOUDLE_DIR = "/src/"  # public, init required, module relative path to ROOT_DIR
    MOUDLE_ABS_DIR = ROOT_DIR + MOUDLE_DIR  # private
    IS_LIB_DEPS = False

    TYPE_MAP:dict = { 
            "app":ModuleType.APP, "qtapp":ModuleType.QtAPP,
            "kit":ModuleType.Lib, "qtkit":ModuleType.LibQt, "lib":ModuleType.LibDeps
        }

    @staticmethod
    def add(root_dir:str, module_type:ModuleType, module_name:str, deps:list=[]):
        print("root_dir =", root_dir, "module_type =", module_type, "module_name =", module_name)
        Module.ROOT_DIR = root_dir
        Module.MOUDLE_ABS_DIR = root_dir + Module.MOUDLE_DIR

        if ModuleType(module_type) is ModuleType.APP:
            Module.add_norm_module(module_name, True)
            Module.add_module_deps(module_name, deps, True)
        elif ModuleType(module_type) is ModuleType.QtAPP:
            Module.add_qt_module(module_name, True)
            Module.add_module_deps(module_name, deps, True)
        elif ModuleType(module_type) is ModuleType.Lib:
            Module.add_norm_module(module_name, False)
            Module.add_module_deps(module_name, deps, False)
        elif ModuleType(module_type) is ModuleType.LibQt:
            Module.add_qt_module(module_name, False)
            Module.add_module_deps(module_name, deps, False)
        elif ModuleType(module_type) is ModuleType.LibDeps:
            Module.add_lib_module(module_name)
        else:
            print("Invalid ModuleType ", module_type)
            for name, value in ModuleType.__members__.items():
                print(name, value)
            return

    @staticmethod
    def add_norm_module(name:str, is_app:bool):
        dst_dir = Module.MOUDLE_ABS_DIR + name
        print("add_norm_module() dst_dir=", dst_dir)
        if Module.check_path(dst_dir):
            cmake_append_str = MODULE_CMAKE_APPEND_LIB_DEPS_NORM if Module.IS_LIB_DEPS else MODULE_CMAKE_APPEND_NORM
            Module.add_module_to_project(cmake_append_str, name)
            if is_app:
                Module.add_module_cmake(dst_dir, name, "bin-deps.cmake")
                Module.add_module_main(dst_dir, "main.cpp.NORM") # add module main.cpp
            elif Module.IS_LIB_DEPS:
                Module.add_module_cmake(dst_dir, name, "lib-deps-norm.cmake")
                Module.add_module_header(dst_dir, name)
            else:
                Module.add_module_cmake(dst_dir, name, "norm.cmake")
                Module.add_module_header(dst_dir, name)
            os.makedirs(dst_dir + "/pimp")
            return True
        return False

    @staticmethod
    def add_qt_module(name:str, is_app:bool):
        dst_dir = Module.MOUDLE_ABS_DIR + name
        print("add_qt_module() dst_dir=", dst_dir)
        if Module.check_path(dst_dir):
            cmake_append_str = MODULE_CMAKE_APPEND_LIB_DEPS_QT if Module.IS_LIB_DEPS else MODULE_CMAKE_APPEND_QT
            Module.add_module_to_project(cmake_append_str, name)
            if is_app:
                Module.add_module_cmake(dst_dir, name, "bin-deps.cmake")
                Module.add_module_main(dst_dir, "main.cpp.QT") # add module main.cpp
            elif Module.IS_LIB_DEPS:
                Module.add_module_cmake(dst_dir, name, "lib-deps-qt.cmake")
                Module.add_module_header(dst_dir, name)
            else:
                Module.add_module_cmake(dst_dir, name, "qt.cmake")
                Module.add_module_header(dst_dir, name)
            os.makedirs(dst_dir + "/Forms")
            os.makedirs(dst_dir + "/Res")
            os.makedirs(dst_dir + "/pimp")
            return True
        return False

    @staticmethod
    def add_lib_module(name:str):
        dst_dir = Module.MOUDLE_ABS_DIR + name
        print("add_lib_module() dst_dir=", dst_dir)
        if Module.check_path(dst_dir):
            # add module lib.cmake
            Module.add_module_to_project(MODULE_CMAKE_APPEND_LIB_THRID_PARTY, name)
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
        print("add_module_to_project: dir_cmake=",dir_cmake)
        pyt_file.File.append_string(dir_cmake, append_str)
        pyt_file.File.replace_string(dir_cmake, "MODULE_NAME", name)
    
    @staticmethod
    def add_module_deps(name:str, deps:list, is_app:bool):
        dir_cmake = Module.MOUDLE_ABS_DIR + name + "/" +  name + ".cmake"
        if len(deps) > 0:
            # dir_name = os.path.basename(os.path.normpath(Module.MOUDLE_ABS_DIR))
            # dir_cmake = Module.MOUDLE_ABS_DIR + dir_name + ".cmake"
            print("add_module_deps: dir_cmake=", dir_cmake)
            lib_deps:str = "set(LIB_DEPS"
            for lib in deps:
                lib_deps = lib_deps + " " + lib
                pyt_file.File.append_string(dir_cmake, MODULE_CMAKE_APPEND_LIB_DEPS)
                pyt_file.File.replace_string(dir_cmake, "MODULE_NAME", lib)
                if is_app:
                    pyt_file.File.replace_string(dir_cmake, "LIB_NAME", "BIN_NAME")
            lib_deps = lib_deps + " )"
            pyt_file.File.replace_string(dir_cmake, "set(LIB_DEPS )", lib_deps)

    @staticmethod
    def check_path(path):
        path=path.strip()       # remove space
        path=path.rstrip("\\")  # remove tail \\
        if os.path.exists(path):
            print("path=%s exist, please backup and remove it, or change your target dir!"%(path))
            return False
        os.makedirs(path) 
        print("path=%s dir create succeed!"%(path))
        return True
