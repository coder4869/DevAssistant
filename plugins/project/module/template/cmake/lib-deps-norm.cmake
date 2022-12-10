set(MODULE_NAMEDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME MODULE_NAME)

FILE(GLOB_RECURSE MODULE_NAME_SRC
    ${MODULE_NAMEDir}/*.h
    ${MODULE_NAMEDir}/*.hpp

    ${MODULE_NAMEDir}/*.c
    ${MODULE_NAMEDir}/*.cc
    ${MODULE_NAMEDir}/*.cpp
    )

if(NOT ANDROID)
    source_group(
        TREE ${MODULE_NAMEDir}
        PREFIX "MODULE_NAME"
        FILES ${MODULE_NAME_SRC}
        )
endif(NOT ANDROID)

add_library(${LIB_NAME} ${LIB_TYPE} ${MODULE_NAME_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${MODULE_NAMEDir} )

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)