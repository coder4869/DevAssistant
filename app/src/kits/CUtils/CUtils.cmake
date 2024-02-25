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

set(CUtilsDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME CUtils)

FILE(GLOB_RECURSE CUtils_SRC
    ${CUtilsDir}/*.h
    ${CUtilsDir}/*.hpp

    ${CUtilsDir}/*.c
    ${CUtilsDir}/*.cc
    ${CUtilsDir}/*.cpp
    )

if(NOT ANDROID)
    source_group(
        TREE ${CUtilsDir}
        PREFIX "CUtils"
        FILES ${CUtils_SRC}
        )
endif(NOT ANDROID)

set(LIB_DEPS ${THIRD_PARTY_LIB} CLog )

add_library(${LIB_NAME} ${LIB_TYPE} ${CUtils_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "kits")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE CUTILS_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_PY} ${CUtilsDir} ${INC_GROUP} )
target_link_directories(${LIB_NAME} PUBLIC ${LIB_LINK_DIR})
target_link_libraries(${LIB_NAME} ${LIB_PY} ${LIB_DEPS} )

if(WITH_PY)
    target_compile_definitions(${LIB_NAME} PRIVATE WITH_PY )
endif(WITH_PY)

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

if(WIN)
    set_target_properties(${LIB_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")
elseif(APPLE)
    # from intern cmake module : apple_func.cmake
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
    XCODE_ADD_INFO_PLIST(${LIB_NAME})
endif(APPLE)

if(CLog)
    add_dependencies(${LIB_NAME} CLog)
else()
    message(FATAL_ERROR "option ON for CLog is required !")
endif(CLog)
