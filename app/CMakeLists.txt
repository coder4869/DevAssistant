# MIT License
# 
# Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Global Config
cmake_minimum_required(VERSION 3.12.0)

# Global Setting
set(PROJ_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_TOOLCHAIN_ROOT ${PROJ_ROOT}/scripts/cmake)
include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/global.cmake)
message("PROJECT_ROOT = ${PROJ_ROOT} ")
message("CMAKE_TOOLCHAIN_ROOT = ${CMAKE_TOOLCHAIN_ROOT} ")
message("include(${CMAKE_TOOLCHAIN_ROOT}/cmake-core/global.cmake) ")


project(${PROJECT_NAME} VERSION 1.0.0.0)
set(LIB_BUILD_TYPE_EXT )
set(LIB_TYPE SHARED) # SHARED STATIC
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
    set(LIB_TYPE STATIC) # SHARED STATIC
    set(WIN32 ON)
    set(OS_TYPE "win")
    set(OS_BUNDLE WIN32)
    add_definitions(-DWIN)

    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-win/win_func.cmake)
    WIN_ADD_META(META_FILES) # Add Resource To Project - eg. AppIcon.ico
    APP_ADD_RES("${CMAKE_TOOLCHAIN_ROOT}/cmake-win/res/*.*"  "Resources/")

elseif(LINUX)
    set(OS_TYPE "linux")
    add_definitions(-DLINUX)

elseif(OSX)
    set(APPLE ON)
    set(OS_TYPE "osx")
    set(OS_BUNDLE MACOSX_BUNDLE)
    set(OS_MIN_VERSION 10.13)
    add_definitions(-DOSX )

    # set OSX Libs
    set(LIB_FMWKs)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/apple_libs.cmake)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/apple_func.cmake)
    XCODE_ADD_META(META_FILES) # Add Resource To Project - eg. Info.plist, AppIcon.icns
    APP_ADD_RES("${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/res/AppIcon.icns"  "Resources/")

elseif(IOS)
    set(APPLE ON)
    set(OS_TYPE "iOS")
    set(OS_MIN_VERSION 10.0)
    add_definitions(-DIOS )

elseif(ANDROID)
    set(OS_TYPE "linux")
    add_definitions(-DANDROID )

endif()


# MODULE options
option(WITH_QT             "Build with Qt                  "	ON)
option(WITH_PY             "Build with python              "	ON)
option(QtDevAssistant      "Build with QtDevAssistant      "	ON)
option(QtProject           "Build with QtProject           "	ON)
option(QtExample           "Build with QtExample           "	ON)
option(QtPractical         "Build with QtPractical         "	ON)
option(QtCustom            "Build with QtCustom            "	ON)
option(QtPlan              "Build with QtPlan              "	ON)
option(QtHelp              "Build with QtHelp              "	ON)
option(QtCoreKit           "Build with QtCoreKit           "	ON)
option(QtScriptsKit        "Build with QtScriptsKit        "	ON)
option(DACoreKit           "Build with DACoreKit           "	ON)
option(QtCryptoKit         "Build with QtCryptoKit         "	ON)
# option(MODULE_OPTION  "Build with MODULE_OPTION" ON)

if(WITH_QT)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-qt/qt_func.cmake)
    QT_INIT(${QT_INSTALL_DIR})

    # set Qt include and libs
    set(INC_QT)
    set(LIB_QT)
    include(${CMAKE_TOOLCHAIN_ROOT}/cmake-qt/qt_libs.cmake)
    message("INC_QT=${INC_QT}")
    message("LIB_QT=${LIB_QT}")
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
set(INC_GROUP  ${PROJ_ROOT}/src/app ${PROJ_ROOT}/src/qtmodules ${PROJ_ROOT}/src/kits ${PROJ_ROOT}/deps)
include(${PROJ_ROOT}/src/app/app.cmake)
include(${PROJ_ROOT}/src/qtmodules/qtmodules.cmake)
include(${PROJ_ROOT}/src/kits/kits.cmake)
include(${PROJ_ROOT}/deps/deps.cmake)
# include(Module-Group.cmake)
# add_subdirectory(Module-Group-Dir)
message("INC_FILES=${INC_FILES}")
message("SRC_FILES=${SRC_FILES}")


################################## project resources ##################################
set(CONF_FILES ${PROJ_ROOT}/conf/project.json)

set(PLUGIN_DIR ${PROJ_ROOT}/../plugins)
File(GLOB_RECURSE PLUGIN_FILEs ${PLUGIN_DIR}/*.*)
if(NOT ANDROID)
    source_group(
        TREE ${PLUGIN_DIR}
        PREFIX "plugins"
        FILES ${PLUGIN_FILEs}
        )
endif(NOT ANDROID)


################################## build ##################################
add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${SRC_FILES} ${META_FILES} ${CONF_FILES} ${PLUGIN_FILEs})

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_FILES} ${INC_QT} ${INC_PY} ${INC_GROUP} )
# target_link_directories(${PROJECT_NAME} PUBLIC ${INC_LIB})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_FMWKs} ${LIB_QT} ${LIB_PY}
        ${OPENGL_gl_LIBRARY} # https://cmake.org/cmake/help/v3.0/module/FindOpenGL.html
        )

APP_ADD_RES("${PROJ_ROOT}/conf/project.json" "Resources/")
APP_ADD_RES_RECURSE("${PLUGIN_DIR}/" "Resources/plugins/" "${PLUGIN_DIR}/*.*")

if(WITH_QT) 
    QT_DEPLOY(${PROJECT_NAME}) # From qt_func.cmake. Deploy Qt Libs To APP 
    target_compile_definitions(${PROJECT_NAME} PRIVATE  
                                $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
                                $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:QT_NO_DEBUG_OUTPUT>)
endif(WITH_QT)

if(WIN)
    WIN_FIX_COMPILER()
    # INSTALL_TARGET(${PROJECT_NAME}) # lib bin exe
elseif(APPLE)
    # from intern cmake module : apple_func.cmake
    XCODE_SETTING(${PROJECT_NAME} ${OS_MIN_VERSION})
    XCODE_ADD_INFO_PLIST()
endif(APPLE)

if(WITH_QT AND QtProject)
    add_dependencies(${PROJECT_NAME} QtProject)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtProject)
endif(QtProject)

if(WITH_QT AND QtExample)
    add_dependencies(${PROJECT_NAME} QtExample)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtExample)
endif(QtExample)

if(WITH_QT AND QtPractical)
    add_dependencies(${PROJECT_NAME} QtPractical)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtPractical)
endif(QtPractical)

if(WITH_QT AND QtCustom)
    add_dependencies(${PROJECT_NAME} QtCustom)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtCustom)
endif(QtCustom)

if(WITH_QT AND QtPlan)
    add_dependencies(${PROJECT_NAME} QtPlan)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtPlan)
endif(QtPlan)

if(WITH_QT AND QtHelp)
    add_dependencies(${PROJECT_NAME} QtHelp)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtHelp)
endif(QtHelp)

if(WITH_QT AND QtCoreKit)
    add_dependencies(${PROJECT_NAME} QtCoreKit)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtCoreKit)
endif(QtCoreKit)

if(WITH_QT AND QtScriptsKit)
    add_dependencies(${PROJECT_NAME} QtScriptsKit)
    target_link_libraries(${PROJECT_NAME} PUBLIC QtScriptsKit)
endif(QtScriptsKit)

if(DACoreKit)
    add_dependencies(${PROJECT_NAME} DACoreKit)
    target_link_libraries(${PROJECT_NAME} PUBLIC DACoreKit)
endif(DACoreKit)
