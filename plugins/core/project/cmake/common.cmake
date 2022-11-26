

function(PROJECT_FIX_VERSION)
if (NOT PROJECT_VERSION_PATCH)
    SET(PROJECT_VERSION_PATCH 0)
endif()

if (NOT PROJECT_VERSION_TWEAK)
    SET(PROJECT_VERSION_TWEAK 0)
endif()
endfunction(PROJECT_FIX_VERSION)


function(PROJECT_ADD_META FILES_TO_INCLUDE)
    if (NOT RESOURCE_FOLDER)
        set(RESOURCE_FOLDER res)
    endif()

    if (NOT ICON_NAME)
        set(ICON_NAME AppIcon)
    endif()

    if (APPLE)
        set(ICON_FILE ${RESOURCE_FOLDER}/${ICON_NAME}.icns)
    elseif (WIN32)
        set(ICON_FILE ${RESOURCE_FOLDER}/${ICON_NAME}.ico)
    endif()

    if (WIN32)
        configure_file("${STUDIO_ROOT_DIR}/cmake/windows_metafile.rc.in"
            "windows_metafile.rc"
            )
        set(RES_FILES "windows_metafile.rc")
        set(CMAKE_RC_COMPILER_INIT windres)
        ENABLE_LANGUAGE(RC)
        SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
    endif()

    if (APPLE)
        set_source_files_properties(${ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

        # Identify MacOS bundle
        set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
        set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
        set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})
        set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
        set(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
    endif()

    if (APPLE)
        set(${FILES_TO_INCLUDE} ${ICON_FILE})
    elseif (WIN32)
        set(${FILES_TO_INCLUDE} ${RES_FILES})
    endif()
endfunction(PROJECT_ADD_META)


function(WIN_FIX_COMPILER)
    if (MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
    endif()
endfunction(WIN_FIX_COMPILER)
