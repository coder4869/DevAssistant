set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")


# QtProject
if(WITH_QT AND QtProject)
    include(${SRC_ROOT}/QtProject/QtProject.cmake)
endif(WITH_QT AND QtProject)



# QtExample
if(WITH_QT AND QtExample)
    include(${SRC_ROOT}/QtExample/QtExample.cmake)
endif(WITH_QT AND QtExample)



# QtPractical
if(WITH_QT AND QtPractical)
    include(${SRC_ROOT}/QtPractical/QtPractical.cmake)
endif(WITH_QT AND QtPractical)



# QtCustom
if(WITH_QT AND QtCustom)
    include(${SRC_ROOT}/QtCustom/QtCustom.cmake)
endif(WITH_QT AND QtCustom)



# QtPlan
if(WITH_QT AND QtPlan)
    include(${SRC_ROOT}/QtPlan/QtPlan.cmake)
endif(WITH_QT AND QtPlan)



# QtHelp
if(WITH_QT AND QtHelp)
    include(${SRC_ROOT}/QtHelp/QtHelp.cmake)
endif(WITH_QT AND QtHelp)

