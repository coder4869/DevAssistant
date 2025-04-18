# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(QtEnvKitDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtEnvKit)

FILE(GLOB_RECURSE QtEnvKit_SRC
    ${QtEnvKitDir}/*.h
    ${QtEnvKitDir}/*.hpp

    ${QtEnvKitDir}/*.c
    ${QtEnvKitDir}/*.cc
    ${QtEnvKitDir}/*.cpp
    ${QtEnvKitDir}/*.m
    ${QtEnvKitDir}/*.mm
    )

FILE(GLOB_RECURSE QtEnvKit_FORMs 
    ${QtEnvKitDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtEnvKit_RES
    ${QtEnvKitDir}/Res/*.qrc
    ${QtEnvKitDir}/Res/*.qml
    ${QtEnvKitDir}/Res/*.js
    )

set(QtEnvKit_SRC ${QtEnvKit_SRC} ${QtEnvKit_FORMs} ${QtEnvKit_RES})

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${QtEnvKitDir}/unused/*)
list (REMOVE_ITEM QtEnvKit_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${QtEnvKitDir}
        PREFIX "QtEnvKit"
        FILES ${QtEnvKit_SRC}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtEnvKit_RES_UIC ${QtEnvKit_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtEnvKit_SRC
set(QtEnvKit_SRC ${QtEnvKit_SRC} ${QtEnvKit_RES_UIC})

set(LIB_DEPS ${THIRD_PARTY_LIB} COSEnv DevEnv QtUIInfra QtCoreKit CUtils CApp )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtEnvKit_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "qtmodules")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE QTENVKIT_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtEnvKitDir} ${INC_GROUP} )
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

if(COSEnv)
    add_dependencies(${LIB_NAME} COSEnv)
else()
    message(FATAL_ERROR "option ON for COSEnv is required !")
endif(COSEnv)

if(DevEnv)
    add_dependencies(${LIB_NAME} DevEnv)
else()
    message(FATAL_ERROR "option ON for DevEnv is required !")
endif(DevEnv)

if(QtUIInfra)
    add_dependencies(${LIB_NAME} QtUIInfra)
else()
    message(FATAL_ERROR "option ON for QtUIInfra is required !")
endif(QtUIInfra)

if(QtCoreKit)
    add_dependencies(${LIB_NAME} QtCoreKit)
else()
    message(FATAL_ERROR "option ON for QtCoreKit is required !")
endif(QtCoreKit)

if(CUtils)
    add_dependencies(${LIB_NAME} CUtils)
else()
    message(FATAL_ERROR "option ON for CUtils is required !")
endif(CUtils)

if(CApp)
    add_dependencies(${LIB_NAME} CApp)
else()
    message(FATAL_ERROR "option ON for CApp is required !")
endif(CApp)
