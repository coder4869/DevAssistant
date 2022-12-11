
set(QtCustomDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME QtCustom)

FILE(GLOB_RECURSE QtCustom_SRC
    ${QtCustomDir}/*.h
    ${QtCustomDir}/*.hpp

    ${QtCustomDir}/*.c
    ${QtCustomDir}/*.cc
    ${QtCustomDir}/*.cpp
    )

FILE(GLOB_RECURSE QtCustom_FORMs 
    ${QtCustomDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE QtCustom_RES
    ${QtCustomDir}/Res/*.qrc
    ${QtCustomDir}/Res/*.qml
    ${QtCustomDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${QtCustomDir}
        PREFIX "QtCustom"
        FILES ${QtCustom_SRC} ${QtCustom_FORMs} ${QtCustom_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(QtCustom_RES_UIC ${QtCustom_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update QtCustom_SRC
set(QtCustom_SRC ${QtCustom_SRC} ${QtCustom_FORMs} ${QtCustom_RES} ${QtCustom_RES_UIC})

add_library(${LIB_NAME} ${LIB_TYPE} ${QtCustom_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${QtCustomDir} )
target_link_libraries(${LIB_NAME} ${LIB_QT})

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)