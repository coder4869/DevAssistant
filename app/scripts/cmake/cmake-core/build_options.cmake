#### Build Optimization 
# https://blog.csdn.net/weixin_33724570/article/details/89731190
# https://blog.csdn.net/weixin_39716160/article/details/116607853

message("Build Options Setting !!!")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7-a")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fix-cortex-a8" CACHE INTERNAL "" FORCE)
endif()

# --fatal-warnings will take all warnings as error, same to -Werror. Here cancel the limit!
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-fatal-warnings" CACHE INTERNAL "" FORCE)

# [clang LTO is broken with __thread variables #498](https://github.com/android-ndk/ndk/issues/498)
# Workaround is -Wl,-plugin-opt=-emulated-tls
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-plugin-opt=-emulated-tls" CACHE INTERNAL "" FORCE)


set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fPIC " CACHE INTERNAL "" FORCE)
if(NOT APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections -Wl,--as-needed" CACHE INTERNAL "" FORCE)
endif(APPLE)

if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE Debug)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# For Debug and RelWithDebInfo
    add_definitions(-D DEBUG)
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)

    add_compile_options(
        "-Wall" "-fexceptions"
        "$<$<CONFIG:Debug>:-O0;-g3;-ggdb>"
        )

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
# For Release and MinSizeRel
    add_definitions(-D NDDEBUG)
    set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

    add_compile_options(
        "-Wall" "-fexceptions"
        "$<$<CONFIG:Release>:-flto;-O3>"
        )

    # set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto -O3 " CACHE INTERNAL "" FORCE)
    if(NOT APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL " CACHE INTERNAL "" FORCE)
    endif(APPLE)
    
    # gold linker has error for Cortex-A53 on aarch64, Remove icf(reduce lib size) for it.
    if((CMAKE_SYSTEM_PROCESSOR STREQUAL "armv7-a") OR (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86") OR (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"))
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--icf=safe" CACHE INTERNAL "" FORCE)
    endif()
    
else()
    message("Unknown CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} !")
endif(CMAKE_BUILD_TYPE)




