# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(QtHelpDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtHelp)

FILE(GLOB_RECURSE QtHelp_SRC
    ${QtHelpDir}/*.h
    ${QtHelpDir}/*.hpp

    ${QtHelpDir}/*.c
    ${QtHelpDir}/*.cc
    ${QtHelpDir}/*.cpp
    ${QtHelpDir}/*.m
    ${QtHelpDir}/*.mm
    )

FILE(GLOB_RECURSE QtHelp_FORMs 
    ${QtHelpDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtHelp_RES
    ${QtHelpDir}/Res/*.qrc
    ${QtHelpDir}/Res/*.qml
    ${QtHelpDir}/Res/*.js
    )

set(QtHelp_SRC ${QtHelp_SRC} ${QtHelp_FORMs} ${QtHelp_RES})

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${QtHelpDir}/unused/*)
list (REMOVE_ITEM QtHelp_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${QtHelpDir}
        PREFIX "QtHelp"
        FILES ${QtHelp_SRC}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtHelp_RES_UIC ${QtHelp_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtHelp_SRC
set(QtHelp_SRC ${QtHelp_SRC} ${QtHelp_RES_UIC})

set(LIB_DEPS ${THIRD_PARTY_LIB} QtUIInfra CApp )

add_library(${LIB_NAME} ${LIB_TYPE} ${QtHelp_SRC})
set_target_properties(${LIB_NAME} PROPERTIES FOLDER "qtmodules")
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/core_func.cmake)
SET_TARGET_CXX_VERSION(${LIB_NAME})
target_compile_definitions(${LIB_NAME} PRIVATE QTHELP_EXPORT )
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${INC_PY} ${QtHelpDir} ${INC_GROUP} )
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

if(CApp)
    add_dependencies(${LIB_NAME} CApp)
else()
    message(FATAL_ERROR "option ON for CApp is required !")
endif(CApp)
