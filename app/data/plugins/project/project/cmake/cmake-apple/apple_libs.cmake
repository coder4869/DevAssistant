# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

if(OSX)
    ## OpenGL && Foundation && Metal && QuartzCore
    find_package(OpenGL REQUIRED)
    find_library(LIB_FOUNDATION Foundation)
    find_library(LIB_QC QuartzCore)
    find_library(LIB_METAL Metal)
    SET(LIB_FMWKs ${LIB_FMWKs} ${OpenGL} ${LIB_FOUNDATION} ${LIB_QC} ${LIB_METAL})
endif(OSX)