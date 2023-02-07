# MIT License
# 
# Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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

# QtCoreKit
if(WITH_QT AND QtCoreKit)
    include(${SRC_ROOT}/QtCoreKit/QtCoreKit.cmake)
endif(WITH_QT AND QtCoreKit)
