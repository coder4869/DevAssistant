set(DACoreKitDir ${CMAKE_CURRENT_LIST_DIR})
set(LIB_NAME DACoreKit)

FILE(GLOB_RECURSE DACoreKit_SRC
    ${DACoreKitDir}/*.h
    ${DACoreKitDir}/*.hpp

    ${DACoreKitDir}/*.c
    ${DACoreKitDir}/*.cc
    ${DACoreKitDir}/*.cpp
    )

if(NOT ANDROID)
    source_group(
        TREE ${DACoreKitDir}
        PREFIX "DACoreKit"
        FILES ${DACoreKit_SRC}
        )
endif(NOT ANDROID)

add_library(${LIB_NAME} ${LIB_TYPE} ${DACoreKit_SRC})
target_include_directories(${LIB_NAME} PRIVATE ${DACoreKitDir} )

# install libs & headers
INSTALL_INC(${CMAKE_CURRENT_LIST_DIR} include/)
INSTALL_TARGET(${LIB_NAME}) # lib bin exe

# from intern cmake module : apple_func.cmake
if(APPLE)
    XCODE_SETTING(${LIB_NAME} ${OS_MIN_VERSION})
endif(APPLE)