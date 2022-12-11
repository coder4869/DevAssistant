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

set(QtDevAssistantDir ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB_RECURSE QtDevAssistant_SRC
    ${QtDevAssistantDir}/*.h
    ${QtDevAssistantDir}/*.hpp

    ${QtDevAssistantDir}/*.c
    ${QtDevAssistantDir}/*.cc
    ${QtDevAssistantDir}/*.cpp
    )

FILE(GLOB_RECURSE QtDevAssistant_FORMs 
    ${QtDevAssistantDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtDevAssistant_RES
    ${QtDevAssistantDir}/Res/*.qrc
    ${QtDevAssistantDir}/Res/*.qml
    ${QtDevAssistantDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtDevAssistantDir}
        PREFIX "QtDevAssistant"
        FILES ${QtDevAssistant_SRC} ${QtDevAssistant_FORMs} ${QtDevAssistant_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtDevAssistant_RES_UIC ${QtDevAssistant_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtDevAssistant_SRC
set(QtDevAssistant_SRC ${QtDevAssistant_SRC} ${QtDevAssistant_FORMs} ${QtDevAssistant_RES} ${QtDevAssistant_RES_UIC})