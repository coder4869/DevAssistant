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
option(QtDevAssistant      "Build with QtDevAssistant      "	ON)
option(QtProject           "Build with QtProject           "	ON)
option(QtExample           "Build with QtExample           "	ON)
option(QtPractical         "Build with QtPractical         "	ON)
option(QtCustom            "Build with QtCustom            "	ON)
option(QtPlan              "Build with QtPlan              "	ON)
option(QtHelp              "Build with QtHelp              "	ON)
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


# subdirectory
set(INC_FILES)
set(SRC_FILES)
include(${PROJ_ROOT}/src/app/app.cmake)
include(${PROJ_ROOT}/src/qtmodules/qtmodules.cmake)
include(${PROJ_ROOT}/src/kits/kits.cmake)
include(${PROJ_ROOT}/deps/deps.cmake)
# include(Module-Group.cmake)
# add_subdirectory(Module-Group-Dir)
message("INC_FILES=${INC_FILES}")
message("SRC_FILES=${SRC_FILES}")


################################## build ##################################
add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${SRC_FILES} ${META_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_FILES} ${INC_QT})
# target_link_directories(${PROJECT_NAME} PUBLIC ${INC_LIB})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_FMWKs} ${LIB_QT}
        ${OPENGL_gl_LIBRARY} # https://cmake.org/cmake/help/v3.0/module/FindOpenGL.html
        )

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


if(DACoreKit)
    add_dependencies(${PROJECT_NAME} DACoreKit)
    target_link_libraries(${PROJECT_NAME} PUBLIC DACoreKit)
endif(DACoreKit)
