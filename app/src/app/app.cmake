# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

# DevAssistant
if(WITH_QT AND DevAssistant)
    include(${SRC_ROOT}/DevAssistant/DevAssistant.cmake)
endif(WITH_QT AND DevAssistant)
