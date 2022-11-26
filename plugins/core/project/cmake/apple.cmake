
function(XCODE_SETTING target_name os_type min_version)

    # Deployment Postprocess
    XCODE_DEPLOYMENT_POSTPROCESSING(${target_name} ${os_type})
    # Generate Debug Symbols 
    XCODE_DEBUG_SYMBOLS(${target_name} ${os_type})
    # XCode Debug Information Format
    XCODE_DEBUG_INFO_FMT(${target_name} ${os_type})
    # XCode Strip Linked Product
    XCODE_STRIP_INSTALLED_PRODUCT(${target_name} ${os_type})

    # IOS && OSX universal
    if(("${os_type}" STREQUAL "IOS") OR ("${os_type}" STREQUAL "OSX"))
        set_target_properties( ${target_name} PROPERTIES
                XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
                XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14"
                XCODE_ATTRIBUTE_GCC_OPTIMIZATION_LEVEL[variant=Release] s
                XCODE_ATTRIBUTE_LLVM_LTO[variant=Release] YES                   
                XCODE_ATTRIBUTE_GCC_INPUT_FILETYPE sourcecode.cpp.objcpp    # objc++
                )  
    endif()
    
    # For IOS
    if("${os_type}" STREQUAL "IOS")
        set_target_properties( ${target_name} PROPERTIES
                XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${min_version}
                XCODE_ATTRIBUTE_ARCHS "arm64"
                XCODE_ATTRIBUTE_SDKROOT iphoneos
                )
        # append flags for XCODE_ATTRIBUTE_GCC_PREPROCESSOR_DEFINITIONS
        target_compile_definitions(${target_name} PRIVATE __IOS__ 
                $<$<CONFIG:Debug>:DEBUG> $<$<CONFIG:Release>:RELEASE>
                # $<$<OR:$<CONFIG:Debug>, $<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
                )
    elseif("${os_type}" STREQUAL "OSX")
        set_target_properties( ${target_name} PROPERTIES
                XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET ${min_version}
                XCODE_ATTRIBUTE_ARCHS "x86_64"
                XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS "--deep" # for Error "codesign": code object is not signed at all
                XCODE_ATTRIBUTE_SDKROOT macosx
                )
        # append flags for XCODE_ATTRIBUTE_GCC_PREPROCESSOR_DEFINITIONS
        target_compile_definitions(${target_name} PRIVATE __OSX__ 
                $<$<CONFIG:Debug>:DEBUG> $<$<CONFIG:Release>:RELEASE>
                # $<$<OR:$<CONFIG:Debug>, $<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
                )
        # ADD_DEFINITIONS($<$<OR:$<CONFIG:MinSizeRel>, $<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
        # ADD_DEFINITIONS($<$<OR:$<CONFIG:MinSizeRel>, $<CONFIG:Release>>:QT_NO_DEBUG>)        
    endif()

endfunction(XCODE_SETTING)


# XCode Deployment Postprocessing : Default value is YES after XCode 9.1, always used for app slim down.
# NO  : keep non-essential compile symbol. e.g. debug symbol. 
# YES : delete non-essential compile symbol and protect app. e.g. debug symbol.
function(XCODE_DEPLOYMENT_POSTPROCESSING target_name os_type)
    # IOS && OSX universal
    if(("${os_type}" STREQUAL "IOS") OR ("${os_type}" STREQUAL "OSX"))
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=Debug] "NO"
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=MinSizeRel] "YES"
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=RelWithDebInfo] "NO"
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=Release] "YES"
            )  
    endif()
endfunction(XCODE_DEPLOYMENT_POSTPROCESSING)

# XCode Generate Debug Symbols : always used for app slim down.
function(XCODE_DEBUG_SYMBOLS target_name os_type)
    # IOS && OSX universal
    if(("${os_type}" STREQUAL "IOS") OR ("${os_type}" STREQUAL "OSX"))
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Debug] "YES"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=MinSizeRel] "NO"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=RelWithDebInfo] "YES"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Release] "NO"
            )  
    endif()
endfunction(XCODE_DEBUG_SYMBOLS)

# XCode Debug Information Format
function(XCODE_DEBUG_INFO_FMT target_name os_type)
    # IOS && OSX universal
    if(("${os_type}" STREQUAL "IOS") OR ("${os_type}" STREQUAL "OSX"))
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf-with-dsym"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=MinSizeRel] "dwarf"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=RelWithDebInfo] "dwarf-with-dsym"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Release] "dwarf"
            )  
    endif()
endfunction(XCODE_DEBUG_INFO_FMT)

# XCode Strip Linked Product
function(XCODE_STRIP_INSTALLED_PRODUCT target_name os_type)
    # IOS && OSX universal
    if(("${os_type}" STREQUAL "IOS") OR ("${os_type}" STREQUAL "OSX"))
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=Debug] "NO"
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=MinSizeRel] "YES"
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=RelWithDebInfo] "NO"
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=Release] "YES"
            )  
    endif()
endfunction(XCODE_STRIP_INSTALLED_PRODUCT)


# Strip Debug Symbols During Copy
# function(XCODE_DEBUG_SYMBOLS_DURING_COPY target_name os_type)
#     # IOS && OSX universal
#     if(("${os_type}" STREQUAL "IOS") OR ("${os_type}" STREQUAL "OSX"))
#         set_target_properties( ${target_name} PROPERTIES
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "NO"
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=MinSizeRel] "YES"
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=RelWithDebInfo] "NO"
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Release] "YES"
#             )  
#     endif()
# endfunction(XCODE_DEBUG_SYMBOLS_DURING_COPY)

# configure_file(${CMAKE_SOURCE_DIR}/Info.plist.in ${CMAKE_BINARY_DIR}/Info.plist)
# set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_BINARY_DIR}/Info.plist)

################################## Demos ##################################

# XCODE_SETTING(<SDK> "IOS"/"OSX" 9.0/10.10)