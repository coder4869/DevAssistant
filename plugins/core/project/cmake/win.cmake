

function(PROJECT_FIX_VERSION)
    if (NOT PROJECT_VERSION_PATCH)
        SET(PROJECT_VERSION_PATCH 0)
    endif()

    if (NOT PROJECT_VERSION_TWEAK)
        SET(PROJECT_VERSION_TWEAK 0)
    endif()
endfunction(PROJECT_FIX_VERSION)


function(PROJECT_ADD_META FILES_TO_INCLUDE)
    set(ICON_FILE res/AppIcon.ico)
    configure_file("${STUDIO_ROOT_DIR}/cmake/windows_metafile.rc.in"
        "windows_metafile.rc"
        )
    set(RES_FILES "windows_metafile.rc")
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
    set(${FILES_TO_INCLUDE} ${RES_FILES})
endfunction(PROJECT_ADD_META)


function(WIN_FIX_COMPILER)
    if (MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
    endif()
endfunction(WIN_FIX_COMPILER)
