# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(QtExampleDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtExample)

FILE(GLOB_RECURSE QtExample_SRC
    ${QtExampleDir}/*.h
    ${QtExampleDir}/*.hpp

    ${QtExampleDir}/*.c
    ${QtExampleDir}/*.cc
    ${QtExampleDir}/*.cpp
    ${QtExampleDir}/*.m
    ${QtExampleDir}/*.mm
    )

FILE(GLOB_RECURSE QtExample_FORMs 
    ${QtExampleDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtExample_RES
    ${QtExampleDir}/Res/*.qrc
    ${QtExampleDir}/Res/*.qml
    ${QtExampleDir}/Res/*.js
    )

set(QtExample_SRC ${QtExample_SRC} ${QtExample_FORMs} ${QtExample_RES})

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${QtExampleDir}/unused/*)
list (REMOVE_ITEM QtExample_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${QtExampleDir}
        PREFIX "QtExample"
        FILES ${QtExample_SRC}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtExample_RES_UIC ${QtExample_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtExample_SRC
set(QtExample_SRC ${QtExample_SRC} ${QtExample_RES_UIC})

set(LIB_DEPS ${THIRD_PARTY_LIB} QtUIInfra CUtils )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtExample_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "qtmodules")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE QTEXAMPLE_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtExampleDir} ${INC_GROUP} )
target_link_directories(${LIB_NAME} PUBLIC ${LIB_LINK_DIR})
target_link_libraries(${LIB_NAME} ${LIB_QT} ${LIB_PY} ${LIB_DEPS})

if(WITH_QT)
    target_compile_definitions(${LIB_NAME} PRIVATE WITH_QT )
endif(WITH_QT)

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

if(QtUIInfra)
    add_dependencies(${LIB_NAME} QtUIInfra)
else()
    message(FATAL_ERROR "option ON for QtUIInfra is required !")
endif(QtUIInfra)

if(CUtils)
    add_dependencies(${LIB_NAME} CUtils)
else()
    message(FATAL_ERROR "option ON for CUtils is required !")
endif(CUtils)
