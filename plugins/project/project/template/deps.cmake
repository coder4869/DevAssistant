# MIT License
# 
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
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

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

set(THIRD_PARTY_INC ${THIRD_PARTY_INC} ${SRC_ROOT}/include)
if(WIN)
    set(LIB_DIR lib_win_x64)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(LIB_DIR lib_win_x86)
    endif()

    FILE(GLOB_RECURSE STATIC_LIBS
        ${SRC_ROOT}/${LIB_DIR}/*.lib
        )
    set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${STATIC_LIBS})
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/*.dll" "Debug/")
    else()
        APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/*.dll" "Release/")
    endif()
endif(WIN)
