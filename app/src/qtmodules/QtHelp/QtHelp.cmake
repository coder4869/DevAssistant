
set(QtHelpDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtHelp)

FILE(GLOB_RECURSE QtHelp_SRC
    ${QtHelpDir}/*.h
    ${QtHelpDir}/*.hpp

    ${QtHelpDir}/*.c
    ${QtHelpDir}/*.cc
    ${QtHelpDir}/*.cpp
    )

FILE(GLOB_RECURSE QtHelp_FORMs 
    ${QtHelpDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtHelp_RES
    ${QtHelpDir}/Res/*.qrc
    ${QtHelpDir}/Res/*.qml
    ${QtHelpDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtHelpDir}
        PREFIX "QtHelp"
        FILES ${QtHelp_SRC} ${QtHelp_FORMs} ${QtHelp_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtHelp_RES_UIC ${QtHelp_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtHelp_SRC
set(QtHelp_SRC ${QtHelp_SRC} ${QtHelp_FORMs} ${QtHelp_RES} ${QtHelp_RES_UIC})

add_library(${LIB_NAME} ${LIB_TYPE} ${QtHelp_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${QtHelpDir} )
target_link_libraries(${LIB_NAME} ${LIB_QT})

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)