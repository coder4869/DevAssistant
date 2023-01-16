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

set(CURRENT_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})

# var META_FILES required
function(WIN_ADD_META)
    if (WIN32)
        set(ICON_FILE ${CURRENT_CMAKE_DIR}/res/AppIcon.ico)

        configure_file("${CURRENT_CMAKE_DIR}/res/windows_metafile.rc.in" "windows_metafile.rc")
        set(RES_FILES "windows_metafile.rc")
        set(CMAKE_RC_COMPILER_INIT windres)
        ENABLE_LANGUAGE(RC)
        SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")

        set(META_FILES ${RES_FILES} ${ICON_FILE} PARENT_SCOPE) # PARENT_SCOPE make change avaliable outside fucntion
    endif()
endfunction(WIN_ADD_META)


function(WIN_FIX_COMPILER bin_name)
    if (MSVC)
        set_target_properties(${bin_name} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
    endif()
endfunction(WIN_FIX_COMPILER)