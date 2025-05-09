# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

# Global Config
cmake_minimum_required(VERSION 3.12.0)

# Global Setting
set(PROJ_ROOT ${CMAKE_CURRENT_LIST_DIR})

if(WIN)
    # set(CMAKE_INSTALL_PREFIX "${PROJ_ROOT}")
    set(EXECUTABLE_OUTPUT_PATH "${PROJ_ROOT}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJ_ROOT}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJ_ROOT}/bin64")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJ_ROOT}/bin64")
    # set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJ_ROOT}/bin64/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJ_ROOT}/lib")
elseif(LINUX)
	set(CMAKE_INSTALL_PREFIX "${PROJ_ROOT}/bin64")
	set(EXECUTABLE_OUTPUT_PATH "${PROJ_ROOT}/bin64")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJ_ROOT}/bin64")
else()
	set(CMAKE_INSTALL_PREFIX "${PROJ_ROOT}/bin64")
	set(EXECUTABLE_OUTPUT_PATH "${PROJ_ROOT}/bin64")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJ_ROOT}/bin64")
	# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJ_ROOT}/bin64/lib")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJ_ROOT}/bin64/lib")
endif()
set(CMAKE_TOOLCHAIN_ROOT ${PROJ_ROOT}/scripts/cmake)
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/global.cmake)
message("PROJECT_ROOT = ${PROJ_ROOT} ")
message("CMAKE_TOOLCHAIN_ROOT = ${CMAKE_TOOLCHAIN_ROOT} ")
message("include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/global.cmake) ")


project(${PROJECT_NAME} VERSION 2.1.0.0)
# set(CMAKE_DEBUG_POSTFIX d)
set(LIB_TYPE SHARED) # SHARED STATIC
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
message("PROJECT_NAME = ${PROJECT_NAME} ")
message("LIB_TYPE = ${LIB_TYPE} ")


# platform options
option(WIN      "Build for Windows"     OFF)
option(LINUX    "Build for Linux"       OFF)
option(OSX      "Build for MacOSX"      OFF)
option(IOS      "Build for IOS"         OFF)
option(ANDROID  "Build for Android"     OFF)

set(META_FILES )
if(WIN)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # required for gen exp
    set(LIB_TYPE STATIC) # SHARED STATIC
    set(WIN32 ON)
    set(OS_TYPE "win")
    set(OS_BUNDLE WIN32)
    add_definitions(-DWIN=1)

    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-win/win_func.cmake)
    WIN_ADD_META(META_FILES) # Add Resource To Project - eg. AppIcon.ico
    APP_ADD_RES("${CMAKE_TOOLCHAIN_ROOT}/cmake-win/res/*.*"  "data/Resource")

elseif(LINUX)
    set(OS_TYPE "linux")
    add_definitions(-DLINUX=1)

    if("${LINUX_OS}" STREQUAL "CentOS")
        set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/Qt5")
    elseif("${LINUX_OS}" STREQUAL "Ubuntu")
        set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake")
    endif(LINUX_OS)
    message("CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")

    if(WITH_QT)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    endif(WITH_QT)

elseif(OSX)
    set(APPLE ON)
    set(OS_TYPE "osx")
    set(OS_BUNDLE MACOSX_BUNDLE)
    set(OS_MIN_VERSION 10.15)
    # developer team id, not apple id email
    # https://developer.apple.com/cn/help/account/manage-your-team/locate-your-team-id
    set(XCODE_DEVELOPMENT_TEAM "")
    set(XCODE_CODE_SIGN_IDENTITY "")
    set(XCODE_PROVISIONING_PROFILE "")
    add_definitions(-DOSX=1)

    # set OSX Libs
    set(LIB_FMWKs)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/apple_libs.cmake)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/apple_func.cmake)
    XCODE_ADD_META(META_FILES) # Add Resource To Project - eg. Info.plist, AppIcon.icns
    APP_ADD_RES("${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/res/AppIcon.icns"  "Resources")
    set(META_FILES ${META_FILES} ${PROJECT_BINARY_DIR}/Info.plist)

elseif(IOS)
    set(APPLE ON)
    set(OS_TYPE "iOS")
    set(OS_MIN_VERSION 13.0)
    # developer team id, not apple id email
    # https://developer.apple.com/cn/help/account/manage-your-team/locate-your-team-id
    set(XCODE_DEVELOPMENT_TEAM "XXXXXXXXXX")
    set(XCODE_CODE_SIGN_IDENTITY "Apple Development")
    set(XCODE_PROVISIONING_PROFILE "")
    add_definitions(-DIOS=1)

    # set iOS Libs
    set(LIB_FMWKs)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/apple_libs.cmake)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/apple_func.cmake)
    XCODE_ADD_META(META_FILES) # Add Resource To Project - eg. Info.plist, AppIcon.icns
    APP_ADD_RES("${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/res/AppIcon.icns"  "Resources")
    set(META_FILES ${META_FILES} ${PROJECT_BINARY_DIR}/Info.plist)

elseif(ANDROID)
    set(OS_TYPE "linux")
    add_definitions(-DANDROID=1)

endif()


# project resources
# set(CONF_FILES ${PROJ_ROOT}/conf/project.json)
set(CONF_DIR ${PROJ_ROOT}/conf)
File(GLOB_RECURSE CONF_FILES ${CONF_DIR}/*.*)
if(NOT ANDROID)
    source_group(
        TREE ${CONF_DIR}
        PREFIX "conf"
        FILES ${CONF_FILES}
        )
endif(NOT ANDROID)

set(DATA_DIR ${PROJ_ROOT}/data)
File(GLOB_RECURSE DATA_FILES ${DATA_DIR}/*.*)
if(NOT ANDROID)
    source_group(
        TREE ${DATA_DIR}
        PREFIX "data"
        FILES ${DATA_FILES}
        )
endif(NOT ANDROID)

set(TOOL_DIR ${PROJ_ROOT}/tools)
File(GLOB_RECURSE TOOL_FILEs ${TOOL_DIR}/*.*)
if(NOT ANDROID)
    source_group(
        TREE ${TOOL_DIR}
        PREFIX "tools"
        FILES ${TOOL_FILEs}
        )
endif(NOT ANDROID)


# MODULE options
option(WITH_PY             "Build with PY                  "	OFF)
option(WITH_QT             "Build with QT                  "	ON)
option(DevAssistant        "Build with DevAssistant        "	ON)
option(QtProject           "Build with QtProject           "	ON)
option(QtExample           "Build with QtExample           "	ON)
option(QtPractical         "Build with QtPractical         "	ON)
option(QtCustom            "Build with QtCustom            "	ON)
option(QtPlan              "Build with QtPlan              "	ON)
option(QtHelp              "Build with QtHelp              "	ON)
option(QtEnvKit            "Build with QtEnvKit            "	ON)
option(QtUIInfra           "Build with QtUIInfra           "	ON)
option(QtCoreKit           "Build with QtCoreKit           "	ON)
option(COSEnv              "Build with COSEnv              "	ON)
option(CUtils              "Build with CUtils              "	ON)
option(CScript             "Build with CScript             "	ON)
option(CApp                "Build with CApp                "	ON)
option(GitTool             "Build with GitTool             "	ON)
option(DevEnv              "Build with DevEnv              "	ON)
option(QtCryptoKit         "Build with QtCryptoKit         "	ON)
# option(MODULE_OPTION  "Build with MODULE_OPTION" ON)

SET(LIB_LINK_DIR ${CMAKE_BINARY_DIR} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

if(WITH_QT)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-qt/qt_func.cmake)
    QT_INIT(${QT_INSTALL_DIR})
    SET(LIB_LINK_DIR ${QT_INSTALL_DIR}/bin ${LIB_LINK_DIR})

    # set Qt include and libs
    set(INC_QT)
    set(LIB_QT)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-qt/qt_libs.cmake)
    message("INC_QT=${INC_QT}")
    message("LIB_QT=${LIB_QT}")

    if(MSVC)
        set(CMAKE_AUTOMOC_RELAXED_MODE 1)  # avoid moc encoding issue
        set(CMAKE_AUTOMOC_MACRO_NAMES "Q_OBJECT;Q_GADGET;Q_NAMESPACE")
        add_compile_definitions(_CRT_SECURE_NO_WARNINGS)  # Optional, disable security warning
    endif(MSVC)
endif(WITH_QT)

if(WITH_PY)
    # set Qt include and libs
    set(INC_PY)
    set(LIB_PY)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-py/py_libs.cmake)
    message("INC_PY=${INC_PY}")
    message("LIB_PY=${LIB_PY}")
endif(WITH_PY)


# subdirectory
set(INC_FILES)
set(SRC_FILES)
set(THIRD_PARTY_INC)
set(THIRD_PARTY_INC_FILES)
set(THIRD_PARTY_LIB)
set(INC_GROUP  ${PROJ_ROOT}/src/app ${PROJ_ROOT}/src/qtmodules ${PROJ_ROOT}/src/kits ${PROJ_ROOT}/src/tool ${PROJ_ROOT}/deps)
# include(Module-Group.cmake)
include(${PROJ_ROOT}/deps/deps.cmake)
set(INC_GROUP ${THIRD_PARTY_INC} ${INC_GROUP})
include(${PROJ_ROOT}/src/tool/tool.cmake)
include(${PROJ_ROOT}/src/kits/kits.cmake)
include(${PROJ_ROOT}/src/qtmodules/qtmodules.cmake)
include(${PROJ_ROOT}/src/app/app.cmake)
# add_subdirectory(Module-Group-Dir)
message("INC_GROUP=${INC_GROUP}")
message("INC_FILES=${INC_FILES}")
message("SRC_FILES=${SRC_FILES}")


message("CMAKE_HOST_SYSTEM_NAME = ${CMAKE_HOST_SYSTEM_NAME}")
message("CMAKE_HOST_SYSTEM_PROCESSOR = ${CMAKE_HOST_SYSTEM_PROCESSOR}")