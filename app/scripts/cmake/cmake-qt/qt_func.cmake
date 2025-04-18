# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

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
        FIND_PACKAGE(PkgConfig REQUIRED)
    elseif(OSX)  # MacOSX
        SET(Qt5_DIR "${install_dir}/lib/cmake/Qt5" CACHE PATH "Path to Qt5 cmake stuff: ../5.14.2/clang_64/lib/cmake/Qt5" )
        FIND_PACKAGE(PkgConfig REQUIRED)
    endif()
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
    elseif(OSX)  # MacOSX
        SET(DEPLOYQT_EXEC "${DEPLOYQT_EXEC}/macdeployqt")
        add_custom_command(TARGET ${target_name} 
            POST_BUILD
            COMMAND ${DEPLOYQT_EXEC} "$<TARGET_BUNDLE_DIR:${target_name}>" -qmldir=${CMAKE_SOURCE_DIR} 
            )
    endif()
endfunction(QT_DEPLOY)
