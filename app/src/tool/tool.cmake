# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

# GitTool
if(GitTool)
    include(${SRC_ROOT}/GitTool/GitTool.cmake)
endif(GitTool)

# DevEnv
if(DevEnv)
    include(${SRC_ROOT}/DevEnv/DevEnv.cmake)
endif(DevEnv)
