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

set(QtExampleDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtExample)

FILE(GLOB_RECURSE QtExample_SRC
    ${QtExampleDir}/*.h
    ${QtExampleDir}/*.hpp

    ${QtExampleDir}/*.c
    ${QtExampleDir}/*.cc
    ${QtExampleDir}/*.cpp
    )

FILE(GLOB_RECURSE QtExample_FORMs 
    ${QtExampleDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtExample_RES
    ${QtExampleDir}/Res/*.qrc
    ${QtExampleDir}/Res/*.qml
    ${QtExampleDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtExampleDir}
        PREFIX "QtExample"
        FILES ${QtExample_SRC} ${QtExample_FORMs} ${QtExample_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtExample_RES_UIC ${QtExample_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtExample_SRC
set(QtExample_SRC ${QtExample_SRC} ${QtExample_FORMs} ${QtExample_RES} ${QtExample_RES_UIC})

set(LIB_DEPS ${THIRD_PARTY_LIB} QtUIInfra )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtExample_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "qtmodules")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE QTEXAMPLE_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtExampleDir} ${INC_GROUP} )
target_link_directories(${LIB_NAME} PUBLIC ${LIB_LINK_DIR})
target_link_libraries(${LIB_NAME} ${LIB_QT} ${LIB_PY} ${LIB_DEPS})

if(WITH_QT)
    target_compile_definitions(${LIB_NAME} PRIVATE WITH_QT )
endif(WITH_QT)

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

if(QtUIInfra)
    add_dependencies(${LIB_NAME} QtUIInfra)
else()
    message(FATAL_ERROR "option ON for QtUIInfra is required !")
endif(QtUIInfra)
