# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

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

# QtEnvKit
if(WITH_QT AND QtEnvKit)
    include(${SRC_ROOT}/QtEnvKit/QtEnvKit.cmake)
endif(WITH_QT AND QtEnvKit)

# QtUIInfra
if(WITH_QT AND QtUIInfra)
    include(${SRC_ROOT}/QtUIInfra/QtUIInfra.cmake)
endif(WITH_QT AND QtUIInfra)

# QtCoreKit
if(WITH_QT AND QtCoreKit)
    include(${SRC_ROOT}/QtCoreKit/QtCoreKit.cmake)
endif(WITH_QT AND QtCoreKit)
