# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(MODULE_NAMEDir ${CMAKE_CURRENT_LIST_DIR})

FILE(GLOB_RECURSE MODULE_NAME_SRC
    ${MODULE_NAMEDir}/*.h
    ${MODULE_NAMEDir}/*.hpp

    ${MODULE_NAMEDir}/*.c
    ${MODULE_NAMEDir}/*.cc
    ${MODULE_NAMEDir}/*.cpp
    ${MODULE_NAMEDir}/*.m
    ${MODULE_NAMEDir}/*.mm
    )

# remove unused files from project
FILE(GLOB_RECURSE unused_files ${MODULE_NAMEDir}/unused/*)
list (REMOVE_ITEM MODULE_NAME_SRC ${unused_files})

if(NOT ANDROID)
    source_group(
        TREE ${MODULE_NAMEDir}
        PREFIX "MODULE_NAME"
        FILES ${MODULE_NAME_SRC}
        )
endif(NOT ANDROID)
