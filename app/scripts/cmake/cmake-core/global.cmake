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

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_CURRENT_LIST_DIR}/core_func.cmake)
message("include(${CMAKE_CURRENT_LIST_DIR}/core_func.cmake) ")
SET_POLICY()
SET_CXX_VERSION("c++17")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # Gen Debug Info

# Compiler
function(SET_COMPILER compiler)
    if("${compiler}" STREQUAL "gcc")
        set(CMAKE_C_COMPILER "/usr/local/gcc/bin/gcc")
        set(CMAKE_CXX_COMPILER "/usr/local/gcc/bin/g++")
        include(${CMAKE_CURRENT_LIST_DIR}/build_gcc.cmake)

        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
        set(CMAKE_FIND_LIBRARY_SUFFIXES .so ${CMAKE_FIND_LIBRARY_SUFFIXES})
        message("include(${CMAKE_CURRENT_LIST_DIR}/build_gcc.cmake) ")

    elseif ("${compiler}" STREQUAL "clang")
        set(CMAKE_C_COMPILER "/usr/bin/clang")
        set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

        set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
        set(CMAKE_FIND_LIBRARY_SUFFIXES .so ${CMAKE_FIND_LIBRARY_SUFFIXES})
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dylib ${CMAKE_FIND_LIBRARY_SUFFIXES})

        include(${CMAKE_CURRENT_LIST_DIR}/build_clang.cmake)
        message("include(${CMAKE_CURRENT_LIST_DIR}/build_clang.cmake) ")

    elseif ("${compiler}" STREQUAL "nmake")
        set(CMAKE_FIND_LIBRARY_SUFFIXES .dll ${CMAKE_FIND_LIBRARY_SUFFIXES})
        set(CMAKE_FIND_LIBRARY_SUFFIXES .lib ${CMAKE_FIND_LIBRARY_SUFFIXES})
        
        # set(CMAKE_GENERATOR "NMake Makefiles" CACHE INTERNAL "" FORCE)
        include(${CMAKE_CURRENT_LIST_DIR}/build_nmake.cmake)
        message("NMake")
    endif()
endfunction(SET_COMPILER)

if(WIN)
    SET_COMPILER("nmake")
elseif(APPLE OR ANDROID)
    SET_COMPILER("clang")
else()
    SET_COMPILER("gcc")
endif(WIN)

