# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(QtCoreKitDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtCoreKit)

FILE(GLOB_RECURSE QtCoreKit_SRC
    ${QtCoreKitDir}/*.h
    ${QtCoreKitDir}/*.hpp

    ${QtCoreKitDir}/*.c
    ${QtCoreKitDir}/*.cc
    ${QtCoreKitDir}/*.cpp
    ${QtCoreKitDir}/*.m
    ${QtCoreKitDir}/*.mm
    )

FILE(GLOB_RECURSE QtCoreKit_FORMs 
    ${QtCoreKitDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtCoreKit_RES
    ${QtCoreKitDir}/Res/*.qrc
    ${QtCoreKitDir}/Res/*.qml
    ${QtCoreKitDir}/Res/*.js
    )

set(QtCoreKit_SRC ${QtCoreKit_SRC} ${QtCoreKit_FORMs} ${QtCoreKit_RES})

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${QtCoreKitDir}/unused/*)
list (REMOVE_ITEM QtCoreKit_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${QtCoreKitDir}
        PREFIX "QtCoreKit"
        FILES ${QtCoreKit_SRC}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtCoreKit_RES_UIC ${QtCoreKit_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtCoreKit_SRC
set(QtCoreKit_SRC ${QtCoreKit_SRC} ${QtCoreKit_RES_UIC})

set(LIB_DEPS ${THIRD_PARTY_LIB} CUtils )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtCoreKit_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "qtmodules")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE QTCOREKIT_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtCoreKitDir} ${INC_GROUP} )
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

if(CUtils)
    add_dependencies(${LIB_NAME} CUtils)
else()
    message(FATAL_ERROR "option ON for CUtils is required !")
endif(CUtils)
