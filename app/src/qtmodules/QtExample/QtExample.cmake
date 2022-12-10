
set(QtExampleDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtExample)

FILE(GLOB_RECURSE QtExample_SRC
    ${QtExampleDir}/*.h
    ${QtExampleDir}/*.hpp

    ${QtExampleDir}/*.c
    ${QtExampleDir}/*.cc
    ${QtExampleDir}/*.cpp
    )

FILE(GLOB_RECURSE QtExample_FORMs 
    ${QtExampleDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtExample_RES
    ${QtExampleDir}/Res/*.qrc
    ${QtExampleDir}/Res/*.qml
    ${QtExampleDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtExampleDir}
        PREFIX "QtExample"
        FILES ${QtExample_SRC} ${QtExample_FORMs} ${QtExample_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtExample_RES_UIC ${QtExample_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtExample_SRC
set(QtExample_SRC ${QtExample_SRC} ${QtExample_FORMs} ${QtExample_RES} ${QtExample_RES_UIC})

add_library(${LIB_NAME} ${LIB_TYPE} ${QtExample_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${QtExampleDir} )
target_link_libraries(${LIB_NAME} ${LIB_QT})

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)