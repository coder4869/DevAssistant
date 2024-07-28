# MIT License
# 
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
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

set(CURRENT_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})

# eg. XCODE_SETTING(<SDK> 9.0/10.13)
function(XCODE_SETTING target_name min_version)
    if(IOS OR OSX)
        # Deployment Postprocess
        XCODE_DEPLOYMENT_POSTPROCESSING(${target_name})
        # Generate Debug Symbols 
        XCODE_DEBUG_SYMBOLS(${target_name})
        # XCode Debug Information Format
        XCODE_DEBUG_INFO_FMT(${target_name})
        # XCode Strip Linked Product
        XCODE_STRIP_INSTALLED_PRODUCT(${target_name})
    
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
            XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++17"
            XCODE_ATTRIBUTE_GCC_OPTIMIZATION_LEVEL[variant=Release] s
            XCODE_ATTRIBUTE_LLVM_LTO[variant=Release] YES                   
            XCODE_ATTRIBUTE_GCC_INPUT_FILETYPE sourcecode.cpp.objcpp    # objc++
            XCODE_ATTRIBUTE_OTHER_CFLAGS[variant=Release] "-fembed-bitcode"
            XCODE_ATTRIBUTE_BITCODE_GENERATION_MODE "bitcode"
            XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO"
            )  
    endif()
    
    if(IOS)
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET ${min_version}
            XCODE_ATTRIBUTE_ARCHS "arm64 ${CMAKE_HOST_SYSTEM_PROCESSOR}" # "x86_64"
            XCODE_ATTRIBUTE_SDKROOT iphoneos
            )
        # append flags for XCODE_ATTRIBUTE_GCC_PREPROCESSOR_DEFINITIONS
        # https://blog.csdn.net/whatday/article/details/104376582/
        # https://www.cnblogs.com/Need4Speak/p/5397949.html
        # add_definitions(-D __IOS__=1)
        target_compile_definitions(${target_name} PUBLIC __IOS__ )
    elseif(OSX)
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET ${min_version}
            XCODE_ATTRIBUTE_ARCHS "${CMAKE_HOST_SYSTEM_PROCESSOR}"  # "x86_64"
            XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS "--deep" # for Error "codesign": code object is not signed at all
            XCODE_ATTRIBUTE_SDKROOT macosx
            )
        # append flags for XCODE_ATTRIBUTE_GCC_PREPROCESSOR_DEFINITIONS
        # add_definitions(-D __OSX__=1)
        target_compile_definitions(${target_name} PUBLIC __OSX__ )
    endif()

endfunction(XCODE_SETTING)


######################################## IOS && OSX universal ########################################

# XCode Deployment Postprocessing : Default value is YES after XCode 9.1, always used for app slim down.
# NO  : keep non-essential compile symbol. e.g. debug symbol. 
# YES : delete non-essential compile symbol and protect app. e.g. debug symbol.
function(XCODE_DEPLOYMENT_POSTPROCESSING target_name)
    if(IOS OR OSX)
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=Debug] "NO"
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=MinSizeRel] "YES"
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=RelWithDebInfo] "NO"
            XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING[variant=Release] "YES"
            )  
    endif()
endfunction(XCODE_DEPLOYMENT_POSTPROCESSING)

# XCode Generate Debug Symbols : always used for app slim down.
function(XCODE_DEBUG_SYMBOLS target_name)
    if(IOS OR OSX)
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Debug] "YES"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=MinSizeRel] "NO"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=RelWithDebInfo] "YES"
            XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS[variant=Release] "NO"
            )  
    endif()
endfunction(XCODE_DEBUG_SYMBOLS)

# XCode Debug Information Format
function(XCODE_DEBUG_INFO_FMT target_name)
    if(IOS OR OSX)
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "dwarf-with-dsym"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=MinSizeRel] "dwarf"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=RelWithDebInfo] "dwarf-with-dsym"
            XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Release] "dwarf"
            )  
    endif()
endfunction(XCODE_DEBUG_INFO_FMT)

# XCode Strip Linked Product
function(XCODE_STRIP_INSTALLED_PRODUCT target_name)
    if(IOS OR OSX)
        set_target_properties( ${target_name} PROPERTIES
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=Debug] "NO"
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=MinSizeRel] "YES"
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=RelWithDebInfo] "NO"
            XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT[variant=Release] "YES"
            )  
    endif()
endfunction(XCODE_STRIP_INSTALLED_PRODUCT)

# Strip Debug Symbols During Copy
# function(XCODE_DEBUG_SYMBOLS_DURING_COPY target_name)
#     if(IOS OR OSX)
#         set_target_properties( ${target_name} PROPERTIES
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Debug] "NO"
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=MinSizeRel] "YES"
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=RelWithDebInfo] "NO"
#             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT[variant=Release] "YES"
#             )  
#     endif()
# endfunction(XCODE_DEBUG_SYMBOLS_DURING_COPY)


######################################## XCode Add Files ########################################

# [CMake中的function和macro](https://blog.csdn.net/fb_941219/article/details/89358576)
# [CMake(Normal Variable And Function)](https://www.cnblogs.com/Braveliu/p/15600782.html)
# var META_FILES required
function(XCODE_ADD_META)
    if (APPLE)
        set(ICON_NAME AppIcon)
        set(ICON_FILE ${CURRENT_CMAKE_DIR}/res/${ICON_NAME}.icns)
        set_source_files_properties(${ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION data/Resource)

        # Identify MacOS bundle
        set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
        set(MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION})
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
        set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})
        set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
        set(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
        
        set(META_FILES ${ICON_FILE} PARENT_SCOPE) # PARENT_SCOPE make change avaliable outside fucntion
    endif()
endfunction(XCODE_ADD_META)


# set(XCODE_DEVELOPMENT_TEAM "111111111@qq.com")
# set(XCODE_CODE_SIGN_IDENTITY "iPhone Developer")
# set(XCODE_PROVISIONING_PROFILE "")
# XCODE_ADD_INFO_PLIST(bin_name)
function(XCODE_ADD_INFO_PLIST bin_name)
    if(IOS OR OSX)
        if (IOS)
            configure_file(${CURRENT_CMAKE_DIR}/res/IOSBundleInfo.plist.in ${PROJECT_BINARY_DIR}/Info.plist)
        elseif(OSX)
            configure_file(${CURRENT_CMAKE_DIR}/res/MacOSXBundleInfo.plist.in ${PROJECT_BINARY_DIR}/Info.plist)
        endif()

        set_target_properties(${bin_name} PROPERTIES XCODE_ATTRIBUTE_INFOPLIST_FILE ${PROJECT_BINARY_DIR}/Info.plist)
        # set_target_properties(${bin_name} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist)
        
        # Set Apple Development ID
        if(NOT "${XCODE_DEVELOPMENT_TEAM}" STREQUAL "")
            set_target_properties(${bin_name} PROPERTIES XCODE_ATTRIBUTE_DEVELOPMENT_TEAM ${XCODE_DEVELOPMENT_TEAM}) 
        endif()

        # Set Code Sign Identifier
        if(NOT "${XCODE_CODE_SIGN_IDENTITY}" STREQUAL "")
            set_target_properties(${bin_name} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${XCODE_CODE_SIGN_IDENTITY}")
        endif()

        # set Provisioning Profile(.mobileprovision) file
        if( EXISTS "${XCODE_PROVISIONING_PROFILE}" )  # "path/to/provisioning_profile.mobileprovision"
            get_filename_component(file_name ${XCODE_PROVISIONING_PROFILE} NAME)
            string(FIND ${file_name} ".mobileprovision" suffix_pos)
            if(NOT ${suffix_pos} EQUAL -1)
                set_target_properties(${bin_name} PROPERTIES XCODE_ATTRIBUTE_PROVISIONING_PROFILE "${XCODE_PROVISIONING_PROFILE}")
            else()
                message(STATUS "File ${XCODE_PROVISIONING_PROFILE} exist but not end with .mobileprovision")
            endif()
        else()
            message("Warning: XCODE_ATTRIBUTE_PROVISIONING_PROFILE ${XCODE_PROVISIONING_PROFILE} not exist")
        endif()
    
    endif()
endfunction(XCODE_ADD_INFO_PLIST)