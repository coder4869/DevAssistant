
set(MODULE_NAMEDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME MODULE_NAME)

FILE(GLOB_RECURSE MODULE_NAME_SRC
    ${MODULE_NAMEDir}/*.h
    ${MODULE_NAMEDir}/*.hpp

    ${MODULE_NAMEDir}/*.c
    ${MODULE_NAMEDir}/*.cc
    ${MODULE_NAMEDir}/*.cpp
    )

FILE(GLOB_RECURSE MODULE_NAME_FORMs 
    ${MODULE_NAMEDir}/Forms/*.ui
    )

FILE(GLOB_RECURSE MODULE_NAME_RES
    ${MODULE_NAMEDir}/Res/*.qrc
    ${MODULE_NAMEDir}/Res/*.qml
    ${MODULE_NAMEDir}/Res/*.js
    )

if(NOT ANDROID)
    source_group(
        TREE ${MODULE_NAMEDir}
        PREFIX "MODULE_NAME"
        FILES ${MODULE_NAME_SRC} ${MODULE_NAME_FORMs} ${MODULE_NAME_RES}
        )
endif(NOT ANDROID)

# gen src by forms
qt5_wrap_ui(MODULE_NAME_RES_UIC ${MODULE_NAME_FORMs})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# update MODULE_NAME_SRC
set(MODULE_NAME_SRC ${MODULE_NAME_SRC} ${MODULE_NAME_FORMs} ${MODULE_NAME_RES} ${MODULE_NAME_RES_UIC})

add_library(${LIB_NAME} ${LIB_TYPE} ${MODULE_NAME_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${INC_QT} ${MODULE_NAMEDir} )
target_link_libraries(${LIB_NAME} ${LIB_QT})

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)