set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")


# QtDevAssistant
if(WITH_QT AND QtDevAssistant)
    set(QtDevAssistant_SRC)
    include(${SRC_ROOT}/QtDevAssistant/QtDevAssistant.cmake)
    set(SRC_FILES ${SRC_FILES} ${QtDevAssistant_SRC})
endif(WITH_QT AND QtDevAssistant)

