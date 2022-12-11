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

set(DACoreKitDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME DACoreKit)

FILE(GLOB_RECURSE DACoreKit_SRC
    ${DACoreKitDir}/*.h
    ${DACoreKitDir}/*.hpp

    ${DACoreKitDir}/*.c
    ${DACoreKitDir}/*.cc
    ${DACoreKitDir}/*.cpp
    )

if(NOT ANDROID)
    source_group(
        TREE ${DACoreKitDir}
        PREFIX "DACoreKit"
        FILES ${DACoreKit_SRC}
        )
endif(NOT ANDROID)

add_library(${LIB_NAME} ${LIB_TYPE} ${DACoreKit_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${DACoreKitDir} )

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)