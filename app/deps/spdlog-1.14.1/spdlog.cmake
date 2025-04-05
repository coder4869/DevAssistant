# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

set(THIRD_PARTY_INC ${THIRD_PARTY_INC} ${SRC_ROOT}/include)
FILE(GLOB_RECURSE inc_files
    ${SRC_ROOT}/include/*.h
    ${SRC_ROOT}/include/*.hpp
    )
set(THIRD_PARTY_INC_FILES ${THIRD_PARTY_INC_FILES} ${inc_files})

if(WIN)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        FILE(GLOB_RECURSE STATIC_LIBS
            ${SRC_ROOT}/libs/win/x64/*.lib
        )
        set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${STATIC_LIBS})
        APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/*.dll" "Debug/")
    else()
        FILE(GLOB_RECURSE SHARED_LIBS
            ${SRC_ROOT}/libs/win/x64/*.lib
            ${SRC_ROOT}/libs/win/x64/*.dll
        )
        set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${SHARED_LIBS})
        APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/*.dll" "Release/")
    endif()

elseif(IOS)
    FILE(GLOB_RECURSE STATIC_LIBS
        ${SRC_ROOT}/libs/ios/*.a
    )
    # APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/libs/ios/*.a" "deps/spdlog")
elseif(OSX)
    FILE(GLOB_RECURSE STATIC_LIBS
        ${SRC_ROOT}/libs/mac/*.a
    )
elseif(ANDROID)
    FILE(GLOB_RECURSE STATIC_LIBS
        ${SRC_ROOT}/libs/android/*.a
    )
else() # Linux
    if("${LINUX_OS}" STREQUAL "CentOS")
        FILE(GLOB_RECURSE STATIC_LIBS
            ${SRC_ROOT}/libs/centos/arm64/*.a
            )
    elseif("${LINUX_OS}" STREQUAL "Ubuntu")
        FILE(GLOB_RECURSE STATIC_LIBS
            ${SRC_ROOT}/libs/linux/*.a
            )
    endif(LINUX_OS)
endif()

set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${STATIC_LIBS})

if(NOT ANDROID)
    source_group(
        TREE ${SRC_ROOT}
        PREFIX "deps/spdlog"
        FILES ${THIRD_PARTY_LIB} ${inc_files} 
        )
endif(NOT ANDROID)