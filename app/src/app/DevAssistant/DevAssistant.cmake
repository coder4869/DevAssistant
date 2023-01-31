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

set(DevAssistantDir ${CMAKE_CURRENT_LIST_DIR})
set(BIN_NAME DevAssistant)
set(INC_DEPS ${INC_FILES} ${INC_GROUP})
set(LIB_DEPS QtProject QtExample QtPractical QtCustom QtPlan QtHelp QtEnvKit QtCoreKit QtScriptsKit DACoreKit )

FILE(GLOB_RECURSE DevAssistant_SRC
    ${DevAssistantDir}/*.h
    ${DevAssistantDir}/*.hpp

    ${DevAssistantDir}/*.c
    ${DevAssistantDir}/*.cc
    ${DevAssistantDir}/*.cpp
    )

# Special For Qt
if(WITH_QT)
    FILE(GLOB_RECURSE DevAssistant_FORMs 
        ${DevAssistantDir}/Forms/*.ui
        )

    FILE(GLOB_RECURSE DevAssistant_RES
        ${DevAssistantDir}/Res/*.qrc
        ${DevAssistantDir}/Res/*.qml
        ${DevAssistantDir}/Res/*.js
        )

    # gen src by forms
    # qt5_wrap_ui(DevAssistant_RES_UIC ${DevAssistant_FORMs})
    # set(DevAssistant_SRC ${DevAssistant_SRC} ${DevAssistant_FORMs} ${DevAssistant_RES} ${DevAssistant_RES_UIC})

    set(DevAssistant_SRC ${DevAssistant_SRC} ${DevAssistant_FORMs} ${DevAssistant_RES})

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
        TREE ${DevAssistantDir}
        PREFIX "DevAssistant"
        FILES ${DevAssistant_SRC}
        )
endif(NOT ANDROID)

if(WITH_QT)
    # gen src by forms
    qt5_wrap_ui(DevAssistant_RES_UIC ${DevAssistant_FORMs})
    set(DevAssistant_SRC ${DevAssistant_SRC} ${DevAssistant_RES_UIC})
endif()


################################## build bin ##################################
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${BIN_NAME} ${OS_BUNDLE} ${DevAssistant_SRC} ${META_FILES} ${CONF_FILES} ${PLUGIN_FILEs})
target_include_directories(${BIN_NAME} PUBLIC ${INC_DEPS} ${DevAssistantDir} )
# target_link_directories(${BIN_NAME} PUBLIC ${INC_LIB})
target_link_libraries(${BIN_NAME} PUBLIC ${LIB_FMWKs} ${LIB_DEPS}
        ${OPENGL_gl_LIBRARY} # https://cmake.org/cmake/help/v3.0/module/FindOpenGL.html
        )

# add app res
APP_ADD_RES("${PROJ_ROOT}/conf/project.json" "Resources/")
APP_ADD_RES_RECURSE("${PLUGIN_DIR}/" "Resources/plugins/" "${PLUGIN_DIR}/*.*")

if(WITH_QT) 
    QT_DEPLOY(${BIN_NAME}) # From qt_func.cmake. Deploy Qt Libs To APP 
    target_compile_definitions(${BIN_NAME} PRIVATE
                                $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
                                $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:QT_NO_DEBUG_OUTPUT>)
endif(WITH_QT)

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
# INSTALL_TARGET(${BIN_NAME}) # lib bin exe
if(WIN)
    WIN_FIX_COMPILER(${BIN_NAME})
    # INSTALL_TARGET(${BIN_NAME}) # lib bin exe
elseif(APPLE)
    # from intern cmake module : apple_func.cmake
    XCODE_SETTING(${BIN_NAME} ${OS_MIN_VERSION})
    XCODE_ADD_INFO_PLIST(${BIN_NAME})
endif(APPLE)

if(QtProject)
    add_dependencies(${BIN_NAME} QtProject)
else()
    message(FATAL_ERROR "option ON for QtProject is required !")
endif(QtProject)

if(QtExample)
    add_dependencies(${BIN_NAME} QtExample)
else()
    message(FATAL_ERROR "option ON for QtExample is required !")
endif(QtExample)

if(QtPractical)
    add_dependencies(${BIN_NAME} QtPractical)
else()
    message(FATAL_ERROR "option ON for QtPractical is required !")
endif(QtPractical)

if(QtCustom)
    add_dependencies(${BIN_NAME} QtCustom)
else()
    message(FATAL_ERROR "option ON for QtCustom is required !")
endif(QtCustom)

if(QtPlan)
    add_dependencies(${BIN_NAME} QtPlan)
else()
    message(FATAL_ERROR "option ON for QtPlan is required !")
endif(QtPlan)

if(QtHelp)
    add_dependencies(${BIN_NAME} QtHelp)
else()
    message(FATAL_ERROR "option ON for QtHelp is required !")
endif(QtHelp)

if(QtEnvKit)
    add_dependencies(${BIN_NAME} QtEnvKit)
else()
    message(FATAL_ERROR "option ON for QtEnvKit is required !")
endif(QtEnvKit)

if(QtCoreKit)
    add_dependencies(${BIN_NAME} QtCoreKit)
else()
    message(FATAL_ERROR "option ON for QtCoreKit is required !")
endif(QtCoreKit)

if(QtScriptsKit)
    add_dependencies(${BIN_NAME} QtScriptsKit)
else()
    message(FATAL_ERROR "option ON for QtScriptsKit is required !")
endif(QtScriptsKit)

if(DACoreKit)
    add_dependencies(${BIN_NAME} DACoreKit)
else()
    message(FATAL_ERROR "option ON for DACoreKit is required !")
endif(DACoreKit)
