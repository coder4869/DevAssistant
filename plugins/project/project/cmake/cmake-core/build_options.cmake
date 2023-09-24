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

#### Build Optimization 
# https://blog.csdn.net/weixin_33724570/article/details/89731190
# https://blog.csdn.net/weixin_39716160/article/details/116607853

message("Build Options Setting !!!")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # Gen Debug Info

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7-a")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fix-cortex-a8" CACHE INTERNAL "" FORCE)
endif()

# --fatal-warnings will take all warnings as error, same to -Werror. Here cancel the limit!
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-fatal-warnings" CACHE INTERNAL "" FORCE)

# [clang LTO is broken with __thread variables #498](https://github.com/android-ndk/ndk/issues/498)
# Workaround is -Wl,-plugin-opt=-emulated-tls
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-plugin-opt=-emulated-tls" CACHE INTERNAL "" FORCE)


set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fPIC " CACHE INTERNAL "" FORCE)
if(NOT APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections -Wl,--as-needed" CACHE INTERNAL "" FORCE)
endif(APPLE)

if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE Debug)
    set(LIB_BUILD_TYPE_EXT d)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# For Debug and RelWithDebInfo
    add_definitions(-D DEBUG)
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
    set(LIB_BUILD_TYPE_EXT d)

    add_compile_options(
        "-Wall" "-fexceptions"
        "$<$<CONFIG:Debug>:-O0;-g3;-ggdb>"
        )

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
# For Release and MinSizeRel
    add_definitions(-D NDDEBUG)
    set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

    add_compile_options(
        "-Wall" "-fexceptions"
        "$<$<CONFIG:Release>:-flto;-O3>"
        )

    # set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto -O3 " CACHE INTERNAL "" FORCE)
    if(NOT APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL " CACHE INTERNAL "" FORCE)
    endif(APPLE)
    
    # gold linker has error for Cortex-A53 on aarch64, Remove icf(reduce lib size) for it.
    if((CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7-a") OR (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86") OR (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"))
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--icf=safe" CACHE INTERNAL "" FORCE)
    endif()
    
else()
    message("Unknown CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} !")
endif(CMAKE_BUILD_TYPE)
