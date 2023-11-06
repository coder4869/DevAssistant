# MIT License
# 
# Copyright (c) 2021~2023 [coder4869](https://github.com/coder4869)
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

# e.g. 
# SET(Qt5_INSTALL_DIR "$HOME/Qt/5.14.2/clang_64/")
# QT_INIT(${Qt5_INSTALL_DIR})
macro(QT_INIT install_dir)
    # Let's do the CMake job for us
    set(CMAKE_AUTOMOC ON) # For meta object compiler. Generate moc file when project compiling
    set(CMAKE_AUTORCC ON) # For Resource files
    set(CMAKE_AUTOUIC ON) # For UI files

    # Find Qt5 with modules (CMAKE will take "<package_name>_DIR" as root path for find_package(), eg. Qt5_DIR )
    # Needs to set CMAKE variable Qt5_DIR = path-to-your-qt-innstallation/5.14.2/clang_64/lib/cmake/Qt5 
    if(WIN32 OR WIN) # Windows
        SET(Qt5_DIR "${install_dir}\\lib\\cmake\\Qt5" CACHE PATH "Path to Qt5 cmake stuff: ..\\5.14.2\\msvc2017\\lib\\cmake\\Qt5" )
    else()  # OSX
        SET(Qt5_DIR "${install_dir}/lib/cmake/Qt5" CACHE PATH "Path to Qt5 cmake stuff: ../5.14.2/clang_64/lib/cmake/Qt5" )
    endif()
    FIND_PACKAGE(PkgConfig REQUIRED)
endmacro()


# framework for OSX, dll for Windows. Depends on QT_INIT()
# e.g. QT_DEPLOY(<target_name>)
function(QT_DEPLOY target_name)
    GET_TARGET_PROPERTY(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)          # get qmake file path
    GET_FILENAME_COMPONENT(DEPLOYQT_EXEC ${QT5_QMAKE_EXECUTABLE} PATH) # get qmake dir path

    if(WIN32 OR WIN) # Windows
        SET(DEPLOYQT_EXEC "${DEPLOYQT_EXEC}/windeployqt.exe")
        add_custom_command(TARGET ${target_name}
            POST_BUILD
            COMMAND ${DEPLOYQT_EXEC} "$<TARGET_FILE:${target_name}>" --$<LOWER_CASE:$<CONFIG>> --qmldir ${CMAKE_SOURCE_DIR}
            )
    else()  # OSX
        SET(DEPLOYQT_EXEC "${DEPLOYQT_EXEC}/macdeployqt")
        add_custom_command(TARGET ${target_name} 
            POST_BUILD
            COMMAND ${DEPLOYQT_EXEC} "$<TARGET_BUNDLE_DIR:${target_name}>" -qmldir=${CMAKE_SOURCE_DIR} 
            )
    endif()
endfunction(QT_DEPLOY)
