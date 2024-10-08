# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(QtProjectDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtProject)

FILE(GLOB_RECURSE QtProject_SRC
    ${QtProjectDir}/*.h
    ${QtProjectDir}/*.hpp

    ${QtProjectDir}/*.c
    ${QtProjectDir}/*.cc
    ${QtProjectDir}/*.cpp
    ${QtProjectDir}/*.m
    ${QtProjectDir}/*.mm
    )

FILE(GLOB_RECURSE QtProject_FORMs 
    ${QtProjectDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtProject_RES
    ${QtProjectDir}/Res/*.qrc
    ${QtProjectDir}/Res/*.qml
    ${QtProjectDir}/Res/*.js
    )

set(QtProject_SRC ${QtProject_SRC} ${QtProject_FORMs} ${QtProject_RES})

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${QtProjectDir}/unused/*)
list (REMOVE_ITEM QtProject_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${QtProjectDir}
        PREFIX "QtProject"
        FILES ${QtProject_SRC}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtProject_RES_UIC ${QtProject_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtProject_SRC
set(QtProject_SRC ${QtProject_SRC} ${QtProject_RES_UIC})

set(LIB_DEPS ${THIRD_PARTY_LIB} QtEnvKit QtCoreKit QtUIInfra )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtProject_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "qtmodules")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE QTPROJECT_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtProjectDir} ${INC_GROUP} )
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

if(QtEnvKit)
    add_dependencies(${LIB_NAME} QtEnvKit)
else()
    message(FATAL_ERROR "option ON for QtEnvKit is required !")
endif(QtEnvKit)

if(QtCoreKit)
    add_dependencies(${LIB_NAME} QtCoreKit)
else()
    message(FATAL_ERROR "option ON for QtCoreKit is required !")
endif(QtCoreKit)

if(QtUIInfra)
    add_dependencies(${LIB_NAME} QtUIInfra)
else()
    message(FATAL_ERROR "option ON for QtUIInfra is required !")
endif(QtUIInfra)
