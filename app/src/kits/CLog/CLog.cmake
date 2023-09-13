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

set(CLogDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME CLog)

FILE(GLOB_RECURSE CLog_SRC
    ${CLogDir}/*.h
    ${CLogDir}/*.hpp

    ${CLogDir}/*.c
    ${CLogDir}/*.cc
    ${CLogDir}/*.cpp
    )

if(NOT ANDROID)
    source_group(
        TREE ${CLogDir}
        PREFIX "CLog"
        FILES ${CLog_SRC}
        )
endif(NOT ANDROID)

set(LIB_DEPS )

add_library(${LIB_NAME} ${LIB_TYPE} ${CLog_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "kits")
target_include_directories(${LIB_NAME} PRIVATE ${INC_PY} ${CLogDir} ${INC_GROUP} )
target_link_libraries(${LIB_NAME} ${LIB_PY} ${LIB_DEPS} )

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)
