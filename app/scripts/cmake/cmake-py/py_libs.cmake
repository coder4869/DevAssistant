# MIT License
# 
# Copyright (c) 2021~2023 [coder4869](https://github.com/coder4869)
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

if(WITH_PY)
    if(WIN) # for windows
        SET(INC_PY ${PY_INSTALL_DIR}/include )

        if("${LIB_TYPE}" STREQUAL "STATIC")
            SET(LIB_PY ${PY_INSTALL_DIR}/libs/python3.lib ) 
        else()
            SET(LIB_PY ${PY_INSTALL_DIR}/python3.dll ) 
        endif()

    elseif(OSX) # for MacOSX
        # /Applications/Xcode.app/Contents/Developer/Library
        SET(INC_PY ${PY_INSTALL_DIR}/Frameworks/Python3.framework/Headers ) 
        # SET(LIB_PY ${PY_INSTALL_DIR}/Frameworks/Python3.framework/Python )
        find_library(LIB_PY Python3)
        SET(LIB_FMWKs ${LIB_FMWKs} ${LIB_PY} )
        
    endif(OSX)

endif(WITH_PY)