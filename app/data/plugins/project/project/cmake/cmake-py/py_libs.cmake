# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

if(WITH_PY)
    if(WIN) # for windows
        SET(INC_PY ${PY_INSTALL_DIR}/include )

        if("${LIB_TYPE}" STREQUAL "STATIC")
            SET(LIB_PY ${PY_INSTALL_DIR}/libs/python3.lib ) 
        else()
            SET(LIB_PY ${PY_INSTALL_DIR}/python3.dll ) 
        endif()

    elseif(OSX) # for MacOSX
        # /Applications/Xcode.app/Contents/Developer/Library
        SET(INC_PY ${PY_INSTALL_DIR}/Frameworks/Python3.framework/Headers ) 
        # SET(LIB_PY ${PY_INSTALL_DIR}/Frameworks/Python3.framework/Python )
        find_library(LIB_PY Python3)
        SET(LIB_FMWKs ${LIB_FMWKs} ${LIB_PY} )
        
    endif(OSX)

endif(WITH_PY)