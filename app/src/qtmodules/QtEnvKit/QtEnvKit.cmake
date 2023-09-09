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

set(QtEnvKitDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtEnvKit)

FILE(GLOB_RECURSE QtEnvKit_SRC
    ${QtEnvKitDir}/*.h
    ${QtEnvKitDir}/*.hpp

    ${QtEnvKitDir}/*.c
    ${QtEnvKitDir}/*.cc
    ${QtEnvKitDir}/*.cpp
    )

FILE(GLOB_RECURSE QtEnvKit_FORMs 
    ${QtEnvKitDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtEnvKit_RES
    ${QtEnvKitDir}/Res/*.qrc
    ${QtEnvKitDir}/Res/*.qml
    ${QtEnvKitDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtEnvKitDir}
        PREFIX "QtEnvKit"
        FILES ${QtEnvKit_SRC} ${QtEnvKit_FORMs} ${QtEnvKit_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtEnvKit_RES_UIC ${QtEnvKit_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtEnvKit_SRC
set(QtEnvKit_SRC ${QtEnvKit_SRC} ${QtEnvKit_FORMs} ${QtEnvKit_RES} ${QtEnvKit_RES_UIC})

set(LIB_DEPS QtCoreKit )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtEnvKit_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "modules")
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtEnvKitDir} ${INC_GROUP} )
target_link_libraries(${LIB_NAME} ${LIB_QT} ${LIB_PY} ${LIB_DEPS})

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)

if(QtCoreKit)
    add_dependencies(${LIB_NAME} QtCoreKit)
else()
    message(FATAL_ERROR "option ON for QtCoreKit is required !")
endif(QtCoreKit)
