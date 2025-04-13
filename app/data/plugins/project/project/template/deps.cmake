# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

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
