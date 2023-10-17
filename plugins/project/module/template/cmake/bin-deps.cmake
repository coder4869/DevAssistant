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

set(MODULE_NAMEDir ${CMAKE_CURRENT_LIST_DIR})
set(BIN_NAME MODULE_NAME)
set(INC_DEPS ${INC_FILES} ${INC_GROUP})
set(LIB_DEPS ${THIRD_PARTY_LIB} )

FILE(GLOB_RECURSE MODULE_NAME_SRC
    ${MODULE_NAMEDir}/*.h
    ${MODULE_NAMEDir}/*.hpp

    ${MODULE_NAMEDir}/*.c
    ${MODULE_NAMEDir}/*.cc
    ${MODULE_NAMEDir}/*.cpp
    )

# Special For Qt
if(WITH_QT)
    FILE(GLOB_RECURSE MODULE_NAME_FORMs 
        ${MODULE_NAMEDir}/Forms/*.ui
        )

    FILE(GLOB_RECURSE MODULE_NAME_RES
        ${MODULE_NAMEDir}/Res/*.qrc
        ${MODULE_NAMEDir}/Res/*.qml
        ${MODULE_NAMEDir}/Res/*.js
        )

    # gen src by forms
    # qt5_wrap_ui(MODULE_NAME_RES_UIC ${MODULE_NAME_FORMs})
    # set(MODULE_NAME_SRC ${MODULE_NAME_SRC} ${MODULE_NAME_FORMs} ${MODULE_NAME_RES} ${MODULE_NAME_RES_UIC})

    set(MODULE_NAME_SRC ${MODULE_NAME_SRC} ${MODULE_NAME_FORMs} ${MODULE_NAME_RES})

    set(INC_DEPS ${INC_DEPS} ${INC_QT})
    set(LIB_DEPS ${LIB_DEPS} ${LIB_QT})
endif()

# Special For Python
if(WITH_PY)
    set(INC_DEPS ${INC_DEPS} ${INC_PY})
    set(LIB_DEPS ${LIB_DEPS} ${LIB_PY})
endif(WITH_PY)

# Gen Source Tree
if(NOT ANDROID)
    source_group(
        TREE ${MODULE_NAMEDir}
        PREFIX "MODULE_NAME"
        FILES ${MODULE_NAME_SRC}
        )
endif(NOT ANDROID)

if(WITH_QT)
    # gen src by forms
    qt5_wrap_ui(MODULE_NAME_RES_UIC ${MODULE_NAME_FORMs})
    set(MODULE_NAME_SRC ${MODULE_NAME_SRC} ${MODULE_NAME_RES_UIC})
endif()


################################## build bin ##################################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${BIN_NAME} ${OS_BUNDLE} ${MODULE_NAME_SRC} ${META_FILES} ${CONF_FILES} ${PLUGIN_FILEs})
target_include_directories(${BIN_NAME} PUBLIC ${INC_DEPS} ${MODULE_NAMEDir} )
# target_link_directories(${BIN_NAME} PUBLIC ${INC_LIB})
target_link_directories(${BIN_NAME} PUBLIC ${CMAKE_BINARY_DIR} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
target_link_libraries(${BIN_NAME} PUBLIC ${LIB_FMWKs} ${LIB_DEPS}
        ${OPENGL_gl_LIBRARY} # https://cmake.org/cmake/help/v3.0/module/FindOpenGL.html
        )

# add app res
# APP_ADD_RES("${PROJ_ROOT}/conf/project.json" "conf/")
APP_ADD_RES_RECURSE("${CONF_DIR}/" "conf/" "${CONF_DIR}/*.*")
APP_ADD_RES_RECURSE("${PLUGIN_DIR}/" "data/plugins/" "${PLUGIN_DIR}/*.*")

if(WITH_QT) 
    QT_DEPLOY(${BIN_NAME}) # From qt_func.cmake. Deploy Qt Libs To APP 
    target_compile_definitions(${BIN_NAME} PRIVATE
                                $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
                                $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:QT_NO_DEBUG_OUTPUT>
                                WITH_QT )
endif(WITH_QT)

if(WITH_PY)
    target_compile_definitions(${LIB_NAME} PRIVATE WITH_PY )
endif(WITH_PY)

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
# INSTALL_TARGET(${BIN_NAME}) # lib bin exe
if(WIN)
    set_target_properties(${BIN_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")
    WIN_FIX_COMPILER(${BIN_NAME})
    # INSTALL_TARGET(${BIN_NAME}) # lib bin exe
elseif(APPLE)
    # from intern cmake module : apple_func.cmake
    XCODE_SETTING(${BIN_NAME} ${OS_MIN_VERSION})
    XCODE_ADD_INFO_PLIST(${BIN_NAME})
endif(APPLE)
