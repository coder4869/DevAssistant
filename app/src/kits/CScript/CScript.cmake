# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(CScriptDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME CScript)

FILE(GLOB_RECURSE CScript_SRC
    ${CScriptDir}/*.h
    ${CScriptDir}/*.hpp

    ${CScriptDir}/*.c
    ${CScriptDir}/*.cc
    ${CScriptDir}/*.cpp
    ${CScriptDir}/*.m
    ${CScriptDir}/*.mm
    )

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${CScriptDir}/unused/*)
list (REMOVE_ITEM CScript_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${CScriptDir}
        PREFIX "CScript"
        FILES ${CScript_SRC}
        )
endif(NOT ANDROID)

set(LIB_DEPS ${THIRD_PARTY_LIB} CUtils )

add_library(${LIB_NAME} ${LIB_TYPE} ${CScript_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "kits")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE CSCRIPT_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_PY} ${CScriptDir} ${INC_GROUP} )
target_link_directories(${LIB_NAME} PUBLIC ${LIB_LINK_DIR})
target_link_libraries(${LIB_NAME} ${LIB_PY} ${LIB_DEPS} )

if(WITH_PY)
    target_compile_definitions(${LIB_NAME} PRIVATE WITH_PY )
endif(WITH_PY)

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

if(WIN)
    set_target_properties(${LIB_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")
elseif(APPLE)
    # from intern cmake module : apple_func.cmake
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
    XCODE_ADD_INFO_PLIST(${LIB_NAME})
endif(APPLE)

if(CUtils)
    add_dependencies(${LIB_NAME} CUtils)
else()
    message(FATAL_ERROR "option ON for CUtils is required !")
endif(CUtils)
