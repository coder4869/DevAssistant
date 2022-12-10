
set(QtProjectDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtProject)

FILE(GLOB_RECURSE QtProject_SRC
    ${QtProjectDir}/*.h
    ${QtProjectDir}/*.hpp

    ${QtProjectDir}/*.c
    ${QtProjectDir}/*.cc
    ${QtProjectDir}/*.cpp
    )

FILE(GLOB_RECURSE QtProject_FORMs 
    ${QtProjectDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtProject_RES
    ${QtProjectDir}/Res/*.qrc
    ${QtProjectDir}/Res/*.qml
    ${QtProjectDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtProjectDir}
        PREFIX "QtProject"
        FILES ${QtProject_SRC} ${QtProject_FORMs} ${QtProject_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtProject_RES_UIC ${QtProject_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtProject_SRC
set(QtProject_SRC ${QtProject_SRC} ${QtProject_FORMs} ${QtProject_RES} ${QtProject_RES_UIC})

add_library(${LIB_NAME} ${LIB_TYPE} ${QtProject_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${QtProjectDir} )
target_link_libraries(${LIB_NAME} ${LIB_QT})

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)