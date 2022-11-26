
set(MODULE_NAMEDir ${CMAKE_CURRENT_LIST_DIR})

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
    # Images
    ${MODULE_NAMEDir}/Res/*.jpg
    ${MODULE_NAMEDir}/Res/*.png
    # mesh
    ${MODULE_NAMEDir}/Res/*.mesh
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