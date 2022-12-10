set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")


# DACoreKit
if(DACoreKit)
    include(${SRC_ROOT}/DACoreKit/DACoreKit.cmake)
endif(DACoreKit)

