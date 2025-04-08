# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

# https://wiki.qt.io/Using_CMake_build_system

if(WITH_QT)
    if(WIN) # for windows
        SET(QT_INC_HOME ${QT_INSTALL_DIR}/include)        
        SET(INC_QT ${QT_INC_HOME}
            ${QT_INC_HOME}/QtCore
            ${QT_INC_HOME}/QtGui
            ${QT_INC_HOME}/QtOpenGL
            ${QT_INC_HOME}/QtWidgets
            ${QT_INC_HOME}/QtCharts
            ${QT_INC_HOME}/QtNetwork
            # Camera
            ${QT_INC_HOME}/QtMultimedia
            ${QT_INC_HOME}/QtMultimediaWidgets
            # qml - Quick
            ${QT_INC_HOME}/QtQml
            ${QT_INC_HOME}/QtQuick
            ${QT_INC_HOME}/QtQuickWidgets
            ${QT_INC_HOME}/QtQuickControls2
            # ${QT_INC_HOME}/QtQuick2Plugin
        )
        
        # LIB_EXT = d for debug, empty for release
        SET(LIB_EXT "")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            SET(LIB_EXT "d")
        endif()
        SET(LIB_QT
            ${QT_INSTALL_DIR}/lib/Qt5Core${LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Gui${LIB_EXT}.lib
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
    elseif(LINUX) # for LINUX
        # CentOS
        SET(QT_INC_HOME /usr/include/qt5)       
        SET(QT_LIB_HOME /usr/lib64)   
        # Ubuntu / OpenKylin2.0
        if("${LINUX_OS}" STREQUAL "Ubuntu")
            SET(QT_INC_HOME /usr/include/x86_64-linux-gnu/qt5)       
            SET(QT_LIB_HOME /usr/lib/x86_64-linux-gnu)   
        endif(LINUX_OS)
    
        SET(INC_QT ${QT_INC_HOME}
            ${QT_INC_HOME}/QtCore
            ${QT_INC_HOME}/QtGui
            ${QT_INC_HOME}/QtOpenGL
            ${QT_INC_HOME}/QtWidgets
            ${QT_INC_HOME}/QtCharts
            ${QT_INC_HOME}/QtNetwork
            # Camera
            # ${QT_INC_HOME}/QtMultimedia
            # ${QT_INC_HOME}/QtMultimediaWidgets
            # qml - Quick
            ${QT_INC_HOME}/QtQml
            ${QT_INC_HOME}/QtQuick
            ${QT_INC_HOME}/QtQuickWidgets
            ${QT_INC_HOME}/QtQuickControls2
            # ${QT_INC_HOME}/QtQuick2Plugin
            )
        SET(LIB_QT
            ${QT_LIB_HOME}/libQt5Core.so
            ${QT_LIB_HOME}/libQt5Gui.so
            ${QT_LIB_HOME}/libQt5OpenGL.so
            ${QT_LIB_HOME}/libQt5Widgets.so
            ${QT_LIB_HOME}/libQt5Charts.so
            ${QT_LIB_HOME}/libQt5Network.so
            #${QT_LIB_HOME}/libQt5NetworkAuth.so  
            # Camera
            # ${QT_LIB_HOME}/libQt5Multimedia.so
            # ${QT_LIB_HOME}/libQt5MultimediaWidgets.so
            # qml - Quick
            ${QT_LIB_HOME}/libQt5Qml.so
            ${QT_LIB_HOME}/libQt5Quick.so
            ${QT_LIB_HOME}/libQt5QuickWidgets.so
            # ${QT_LIB_HOME}/libQt5QuickControls2.so
            # ${QT_LIB_HOME}/libQt5Quick2Plugin.so
            )
	    message("INC_QT = ${INC_QT}")
    endif(LINUX)

    # Search QT Libraries
    SET(QT_MODULES Core Gui OpenGL Widgets Charts Network)
    SET(QT_MODULES_QUICK Qml Quick QuickWidgets ) #Quick2Plugin
    if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
        SET(QT_MODULES_CAMERA Multimedia MultimediaWidgets)
        SET(QT_MODULES_QUICK ${QT_MODULES_QUICK} QuickControls2 ) #Quick2Plugin
    endif() 
    # https://blog.csdn.net/wu10188/article/details/129924779
    FIND_PACKAGE(Qt5 COMPONENTS ${QT_MODULES} ${QT_MODULES_CAMERA} ${QT_MODULES_QUICK} REQUIRED)
    # FIND_PACKAGE(Qt5 5.14.2 EXACT COMPONENTS ${QT_MODULES} ${QT_MODULES_CAMERA} ${QT_MODULES_QUICK} REQUIRED)
    set(CMAKE_AUTOUIC OFF)

endif(WITH_QT)