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

# e.g. SET_POLICY()
function(SET_POLICY)
    if (POLICY CMP0048)
        cmake_policy(SET CMP0048 NEW)
    endif()
endfunction(SET_POLICY)


# e.g. SET_CXX_VERSION("17")
# [C++ Standard](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html)
# [add_compile_options() and CMAKE_CXX_FLAGS](http://t.zoukankan.com/Irvingcode-p-12952543.html)
function(SET_CXX_VERSION version)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++${version}")
    else()
        # set(CMAKE_CXX_STANDARD 17)
        # set(CMAKE_CXX_STANDARD_REQUIRED ON)
        # set(CMAKE_CXX_EXTENSIONS OFF)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${version}")
    endif()
    set_property(GLOBAL PROPERTY CXX_STANDARD_VERSION ${version})
endfunction(SET_CXX_VERSION)

# e.g. SET_TARGET_CXX_VERSION("17")
function(SET_TARGET_CXX_VERSION lib_name)
    get_property(CXX_VERSION GLOBAL PROPERTY CXX_STANDARD_VERSION) # Set CXX_VERSION = CXX_STANDARD_VERSION
    message("CXX_VERSION = ${CXX_VERSION}")
    if("${CXX_VERSION}" STREQUAL "11")
        set_property(TARGET ${lib_name} PROPERTY CXX_STANDARD 11)
    elseif("${CXX_VERSION}" STREQUAL "14")
        set_property(TARGET ${lib_name} PROPERTY CXX_STANDARD 14)
    elseif("${CXX_VERSION}" STREQUAL "17")
        set_property(TARGET ${lib_name} PROPERTY CXX_STANDARD 17)
    elseif("${CXX_VERSION}" STREQUAL "20")
        set_property(TARGET ${lib_name} PROPERTY CXX_STANDARD 20)
    else()
        set_property(TARGET ${lib_name} PROPERTY CXX_STANDARD 17)
    endif()
    set_property(TARGET ${lib_name} PROPERTY CXX_STANDARD_REQUIRED ON)
endfunction(SET_TARGET_CXX_VERSION)

# e.g. 
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(CONF_FILES ${PROJ_ROOT}/conf/project.json)
# add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${SRC_FILES} ${CONF_FILES})
# APP_ADD_RES("${PROJ_ROOT}/conf/project.json" "conf/")
function(APP_ADD_RES src_files dst_dir)
    File(GLOB TARGET_FILEs ${src_files})
    # message("APP_ADD_RES() TARGET_FILEs = ${TARGET_FILEs} ; src_files = ${src_files} ; dst_dir = ${dst_dir} ")
    if(APPLE)
        set_source_files_properties(${TARGET_FILEs} PROPERTIES MACOSX_PACKAGE_LOCATION ${dst_dir})
    elseif(WIN32)
        file(COPY ${TARGET_FILEs} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${dst_dir})
    endif(WIN32)
endfunction(APP_ADD_RES)

# e.g. 
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(CONF_FILES ${PROJ_ROOT}/conf/*.json)
# add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${SRC_FILES} ${CONF_FILES})
# APP_ADD_RES_RECURSE_PLAIN("${PROJ_ROOT}/conf/*.json" "conf/")
function(APP_ADD_RES_RECURSE_PLAIN src_files dst_dir)
    File(GLOB_RECURSE TARGET_FILEs ${src_files})
    # message("APP_ADD_RES_RECURSE_PLAIN() TARGET_FILEs = ${TARGET_FILEs} ; src_files = ${src_files} ; dst_dir = ${dst_dir} ")
    if(APPLE)
        foreach(file_path ${TARGET_FILEs})
            set_source_files_properties(${TARGET_FILEs} PROPERTIES MACOSX_PACKAGE_LOCATION ${dst_dir})
        endforeach(file_path)
    elseif(WIN32)
        foreach(file_path ${TARGET_FILEs})
            file(COPY ${TARGET_FILEs} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${dst_dir})
        endforeach(file_path)
    endif(WIN32)
endfunction(APP_ADD_RES_RECURSE_PLAIN)

# e.g. 
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(PLUGIN_DIR ${PROJ_ROOT}/../plugins)
# File(GLOB_RECURSE PLUGIN_FILEs ${PLUGIN_DIR}/*.*)
# if(NOT ANDROID)
#     source_group(
#         TREE ${PLUGIN_DIR}
#         PREFIX "plugins"
#         FILES ${PLUGIN_FILEs}
#         )
# endif(NOT ANDROID)
# add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${SRC_FILES} ${PLUGIN_FILEs})
# APP_ADD_RES_RECURSE("${PLUGIN_DIR}/" "data/plugins/" "${PLUGIN_DIR}/*.*")
function(APP_ADD_RES_RECURSE src_dir dst_dir src_files)
    get_filename_component(src_dir ${src_dir} ABSOLUTE)
    message("APP_ADD_RES_RECURSE() src_dir = ${src_dir} ; dst_dir = ${dst_dir} ; src_files = ${src_files} ")
    File(GLOB_RECURSE TARGET_FILEs ${src_files})
    if(APPLE)
        foreach(file_path ${TARGET_FILEs})
            get_filename_component(file_abs_path ${file_path} ABSOLUTE)
            # get_filename_component(file_abs_path ${file_path} REALPATH)
            get_filename_component(file_dir_path ${file_abs_path} PATH)
            set(dst_path)
            # string(REPLACE <match-string> <replace-string> <out-var> <input>...)
            string(REPLACE ${src_dir} "${dst_dir}/" dst_path ${file_dir_path})
            message("APP_ADD_RES_RECURSE() file_path=${file_path} ; dst_path=${dst_path}")
            set_source_files_properties(${file_path} PROPERTIES MACOSX_PACKAGE_LOCATION ${dst_path})
        endforeach(file_path)
        
    elseif(WIN32)
        foreach(file_path ${TARGET_FILEs})
            get_filename_component(file_abs_path ${file_path} ABSOLUTE)
            # get_filename_component(file_abs_path ${file_path} REALPATH)
            get_filename_component(file_dir_path ${file_abs_path} PATH)
            set(dst_path)
            # string(REPLACE <match-string> <replace-string> <out-var> <input>...)
            string(REPLACE ${src_dir} "${dst_dir}/" dst_path ${file_dir_path})
            message("APP_ADD_RES_RECURSE() file_path=${file_path}; dst_path=${dst_path}")
            file(COPY ${file_path} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/${dst_path})
        endforeach(file_path)
    endif(WIN32)

endfunction(APP_ADD_RES_RECURSE)


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
