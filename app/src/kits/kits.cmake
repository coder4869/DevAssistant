# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

# COSEnv
if(COSEnv)
    include(${SRC_ROOT}/COSEnv/COSEnv.cmake)
endif(COSEnv)

# CUtils
if(CUtils)
    include(${SRC_ROOT}/CUtils/CUtils.cmake)
endif(CUtils)

# CScript
if(CScript)
    include(${SRC_ROOT}/CScript/CScript.cmake)
endif(CScript)

# CApp
if(CApp)
    include(${SRC_ROOT}/CApp/CApp.cmake)
endif(CApp)
