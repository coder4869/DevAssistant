# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_CURRENT_LIST_DIR}/core_func.cmake)
message("include(${CMAKE_CURRENT_LIST_DIR}/core_func.cmake) ")
SET_POLICY()
SET_CXX_VERSION(17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # Gen Debug Info
if(WIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8") # utf-8 
endif(WIN)

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

