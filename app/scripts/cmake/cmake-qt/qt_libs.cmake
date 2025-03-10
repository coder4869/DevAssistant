﻿# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

# https://wiki.qt.io/Using_CMake_build_system

if(WITH_QT)
    if(WIN) # for windows
        SET(INC_QT
            ${QT_INSTALL_DIR}/include
            ${QT_INSTALL_DIR}/include/QtCore
            ${QT_INSTALL_DIR}/include/QtGui
            ${QT_INSTALL_DIR}/include/QtSql
            ${QT_INSTALL_DIR}/include/QtOpenGL
            ${QT_INSTALL_DIR}/include/QtWidgets
            ${QT_INSTALL_DIR}/include/QtCharts
            ${QT_INSTALL_DIR}/include/QtNetwork
            # Camera
            ${QT_INSTALL_DIR}/include/QtMultimedia
            ${QT_INSTALL_DIR}/include/QtMultimediaWidgets
            # qml - Quick
            ${QT_INSTALL_DIR}/include/QtQml
            ${QT_INSTALL_DIR}/include/QtQuick
            ${QT_INSTALL_DIR}/include/QtQuickWidgets
            ${QT_INSTALL_DIR}/include/QtQuickControls2
            # ${QT_INSTALL_DIR}/include/QtQuick2Plugin
        )
        
        # LIB_EXT = d for debug, empty for release
        SET(LIB_EXT "")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            SET(LIB_EXT "d")
        endif()
        SET(LIB_QT
            ${QT_INSTALL_DIR}/lib/Qt5Core${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Gui${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Sql${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5OpenGL${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Widgets${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Charts${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Network${LIB_EXT}.lib
            # Camera
            ${QT_INSTALL_DIR}/lib/Qt5Multimedia${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5MultimediaWidgets${LIB_EXT}.lib
            # qml - Quick
            ${QT_INSTALL_DIR}/lib/Qt5Qml${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Quick${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5QuickWidgets${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5QuickControls2${LIB_EXT}.lib
            # ${QT_INSTALL_DIR}/lib/QtQuick2Plugin${LIB_EXT}.lib            
        ) 
        
    elseif(OSX) # for MacOSX
        SET(INC_QT
            ${QT_INSTALL_DIR}/lib/QtCore.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtGui.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtSql.framework/Headers/
            ${QT_INSTALL_DIR}/lib/QtOpenGL.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtWidgets.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtCharts.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtNetwork.framework/Headers
            # Camera
            ${QT_INSTALL_DIR}/lib/QtMultimedia.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtMultimediaWidgets.framework/Headers
            # qml - Quick
            ${QT_INSTALL_DIR}/lib/QtQml.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtQuick.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtQuickWidgets.framework/Headers
            ${QT_INSTALL_DIR}/lib/QtQuickControls2.framework/Headers
            # ${QT_INSTALL_DIR}/lib/QtQuick2Plugin.framework/Headers
        ) 
        SET(LIB_QT
            ${QT_INSTALL_DIR}/lib/QtCore.framework
            ${QT_INSTALL_DIR}/lib/QtGui.framework
            ${QT_INSTALL_DIR}/lib/QtSql.framework
            ${QT_INSTALL_DIR}/lib/QtOpenGL.framework
            ${QT_INSTALL_DIR}/lib/QtWidgets.framework
            ${QT_INSTALL_DIR}/lib/QtCharts.framework
            ${QT_INSTALL_DIR}/lib/QtNetwork.framework
            # Camera
            ${QT_INSTALL_DIR}/lib/QtMultimedia.framework
            ${QT_INSTALL_DIR}/lib/QtMultimediaWidgets.framework
            # qml - Quick
            ${QT_INSTALL_DIR}/lib/QtQml.framework
            ${QT_INSTALL_DIR}/lib/QtQuick.framework
            ${QT_INSTALL_DIR}/lib/QtQuickWidgets.framework
            ${QT_INSTALL_DIR}/lib/QtQuickControls2.framework
            # ${QT_INSTALL_DIR}/lib/QtQuick2Plugin.framework
            ) 
    endif(OSX)

    # Search QT Libraries
    SET(QT_MODULES Core Gui OpenGL Widgets Charts Network Sql)
    SET(QT_MODULES_CAMERA Multimedia MultimediaWidgets) 
    SET(QT_MODULES_QUICK Qml Quick QuickWidgets QuickControls2 ) #Quick2Plugin
    # https://blog.csdn.net/wu10188/article/details/129924779
    FIND_PACKAGE(Qt5 COMPONENTS ${QT_MODULES} ${QT_MODULES_CAMERA} ${QT_MODULES_QUICK} REQUIRED)
    # FIND_PACKAGE(Qt5 5.14.2 EXACT COMPONENTS ${QT_MODULES} ${QT_MODULES_CAMERA} ${QT_MODULES_QUICK} REQUIRED)
    set(CMAKE_AUTOUIC OFF)

endif(WITH_QT)