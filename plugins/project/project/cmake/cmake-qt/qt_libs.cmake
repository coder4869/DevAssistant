# MIT License

# Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
        
        set(QT_LIB_EXT )
        if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
            set(QT_LIB_EXT d)
        endif()

        SET(LIB_QT
            ${QT_INSTALL_DIR}/lib/Qt5Core${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Gui${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Sql${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5OpenGL${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Widgets${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Charts${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Network${QT_LIB_EXT}.lib
            # Camera
            ${QT_INSTALL_DIR}/lib/Qt5Multimedia${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5MultimediaWidgets${QT_LIB_EXT}.lib
            # qml - Quick
            ${QT_INSTALL_DIR}/lib/Qt5Qml${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5Quick${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5QuickWidgets${QT_LIB_EXT}.lib
            ${QT_INSTALL_DIR}/lib/Qt5QuickControls2${QT_LIB_EXT}.lib
            # ${QT_INSTALL_DIR}/lib/QtQuick2Plugin${QT_LIB_EXT}.lib            
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
    FIND_PACKAGE(Qt5 COMPONENTS ${QT_MODULES} ${QT_MODULES_CAMERA} ${QT_MODULES_QUICK} REQUIRED)
    set(CMAKE_AUTOUIC OFF)

endif(WITH_QT)