# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

# set(THIRD_PARTY_INC ${THIRD_PARTY_INC} ${SRC_ROOT}/include)
# if(WIN)
#     if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#         FILE(GLOB_RECURSE STATIC_LIBS
#             ${SRC_ROOT}/lib_win_x86/*.lib
#         )
#         set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${STATIC_LIBS})
#         APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/*.dll" "Debug/")
#     else()
#         FILE(GLOB_RECURSE SHARED_LIBS
#             ${SRC_ROOT}/lib_win_x64/*.dll
#         )
#         set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${SHARED_LIBS})
#         APP_ADD_RES_RECURSE_PLAIN("${SRC_ROOT}/*.dll" "Release/")
#     endif()
# endif(WIN)

# use input shared var: THIRD_PARTY_INC and THIRD_PARTY_INC_FILES and THIRD_PARTY_LIB
include(${SRC_ROOT}/spdlog-1.14.1/spdlog.cmake)