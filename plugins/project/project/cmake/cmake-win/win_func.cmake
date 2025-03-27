# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(CURRENT_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})

# var META_FILES required
function(WIN_ADD_META)
    if (WIN32)
        # set(ICON_FILE ${CURRENT_CMAKE_DIR}/res/AppIcon.ico)
        set(ICON_FILE ${CURRENT_CMAKE_DIR}/../../../data/Resource/logo.ico)

        configure_file("${CURRENT_CMAKE_DIR}/res/windows_metafile.rc.in" "windows_metafile.rc")
        set(RES_FILES "windows_metafile.rc")
        set(CMAKE_RC_COMPILER_INIT windres)
        ENABLE_LANGUAGE(RC)
        SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")

        set(META_FILES ${RES_FILES} ${ICON_FILE} PARENT_SCOPE) # PARENT_SCOPE make change avaliable outside fucntion
    endif()
endfunction(WIN_ADD_META)


function(WIN_FIX_COMPILER bin_name)
    if (MSVC)
        set_target_properties(${bin_name} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
    endif()
endfunction(WIN_FIX_COMPILER)