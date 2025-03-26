# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")

# use input shared var: THIRD_PARTY_INC and THIRD_PARTY_INC_FILES and THIRD_PARTY_LIB
include(${SRC_ROOT}/spdlog-1.14.1/spdlog.cmake)