﻿# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(MODULE_NAMEDir ${CMAKE_CURRENT_LIST_DIR})
set(BIN_NAME MODULE_NAME)
set(INC_DEPS ${INC_FILES} ${INC_GROUP})
set(LIB_DEPS ${THIRD_PARTY_LIB} )

FILE(GLOB_RECURSE MODULE_NAME_SRC
    ${MODULE_NAMEDir}/*.h
    ${MODULE_NAMEDir}/*.hpp

    ${MODULE_NAMEDir}/*.c
    ${MODULE_NAMEDir}/*.cc
    ${MODULE_NAMEDir}/*.cpp
    ${MODULE_NAMEDir}/*.m
    ${MODULE_NAMEDir}/*.mm
    )

# Special For Python
if(WITH_PY)
    set(INC_DEPS ${INC_DEPS} ${INC_PY})
    set(LIB_DEPS ${LIB_DEPS} ${LIB_PY})
endif(WITH_PY)

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${MODULE_NAMEDir}/unused/*)
list (REMOVE_ITEM MODULE_NAME_SRC ${unused_files})

# Gen Source Tree
if(NOT ANDROID)
    source_group(
        TREE ${MODULE_NAMEDir}
        PREFIX "MODULE_NAME"
        FILES ${MODULE_NAME_SRC}
        )
endif(NOT ANDROID)

################################## build bin ##################################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${BIN_NAME} ${OS_BUNDLE} ${MODULE_NAME_SRC} ${META_FILES} ${CONF_FILES} ${DATA_FILES} ${PLUGIN_FILEs} ${TOOL_FILEs} ${THIRD_PARTY_INC_FILES} ${THIRD_PARTY_LIB} )
set_target_properties(${BIN_NAME} PROPERTIES FOLDER "GROUP_NAME")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${BIN_NAME})
target_include_directories(${BIN_NAME} PUBLIC ${INC_DEPS} ${MODULE_NAMEDir} )
target_link_directories(${BIN_NAME} PUBLIC ${LIB_LINK_DIR})
target_link_libraries(${BIN_NAME} PUBLIC ${LIB_FMWKs} ${LIB_DEPS}
        ${OPENGL_gl_LIBRARY} # https://cmake.org/cmake/help/v3.0/module/FindOpenGL.html
        )
# set_target_properties(${BIN_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# add app res
# APP_ADD_RES("${PROJ_ROOT}/conf/project.json" "conf/")
if(OSX)
    APP_ADD_RES_RECURSE("${CONF_DIR}/" "conf/" "${CONF_DIR}/*")
    APP_ADD_RES_RECURSE("${DATA_DIR}/" "data/" "${DATA_DIR}/*")
    APP_ADD_RES_RECURSE("${TOOL_DIR}/" "tools/" "${TOOL_DIR}/*")
endif(OSX)

if(WITH_PY)
    target_compile_definitions(${LIB_NAME} PRIVATE WITH_PY )
endif(WITH_PY)

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
# INSTALL_TARGET(${BIN_NAME}) # lib bin exe
if(WIN)
    set_target_properties(${BIN_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")
    WIN_FIX_COMPILER(${BIN_NAME})
    # INSTALL_TARGET(${BIN_NAME}) # lib bin exe
elseif(APPLE)
    # from intern cmake module : apple_func.cmake
    XCODE_SETTING(${BIN_NAME} ${OS_MIN_VERSION})
    XCODE_ADD_INFO_PLIST(${BIN_NAME})
endif(APPLE)
