# MIT License

# Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# e.g. SET_POLICY()
function(SET_POLICY)
    if (POLICY CMP0048)
        cmake_policy(SET CMP0048 NEW)
    endif()
endfunction(SET_POLICY)


# e.g. SET_CXX_VERSION("c++17")
# [C++ Standard](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html)
# [add_compile_options() and CMAKE_CXX_FLAGS](http://t.zoukankan.com/Irvingcode-p-12952543.html)
function(SET_CXX_VERSION version)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:${version}")
    else()
        # set(CMAKE_CXX_STANDARD 17)
        # set(CMAKE_CXX_STANDARD_REQUIRED ON)
        # set(CMAKE_CXX_EXTENSIONS OFF)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${version}")
    endif()
endfunction(SET_CXX_VERSION)


# e.g. APP_ADD_RES("${CMAKE_TOOLCHAIN_ROOT}/cmake-apple/res/*.*"  "Resources/")
function(APP_ADD_RES src_files dst_dir)
    File(GLOB TARGET_FILEs ${src_files})
    if(APPLE)
        set_source_files_properties(${TARGET_FILEs} PROPERTIES MACOSX_PACKAGE_LOCATION ${dst_dir})
    elseif(WIN32)
        file(COPY ${TARGET_FILEs} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${dst_dir})
    endif(OSX)    
endfunction(APP_ADD_RES)


# e.g. cmake .. -DCMAKE_INSTALL_PREFIX=$BUILD_DIR
# based on CMAKE_INSTALL_PREFIX
function(INSTALL_INC from_dir to_dir)

    INSTALL(DIRECTORY ${from_dir} DESTINATION  ${to_dir}
        FILES_MATCHING 
        PATTERN "Forms" EXCLUDE # For Qt
        PATTERN "pimp"  EXCLUDE # For Private Implement
        PATTERN "*.h"   PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
        PATTERN "*.hpp" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
        PATTERN "*.inc" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
    )
    
endfunction(INSTALL_INC)

# lib bin exe
function(INSTALL_TARGET sdk_name)
    # include(GNUInstallDirs)
    INSTALL(TARGETS ${sdk_name}
            RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin # exe & dynamic lib
            LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
            ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction(INSTALL_TARGET)
