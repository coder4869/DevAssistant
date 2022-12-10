set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_CURRENT_LIST_DIR}/core_func.cmake)
message("include(${CMAKE_CURRENT_LIST_DIR}/core_func.cmake) ")
SET_POLICY()
SET_CXX_VERSION("c++17")

# Compiler
# set(CMAKE_C_COMPILER "/usr/local/gcc/bin/gcc")
# set(CMAKE_CXX_COMPILER "/usr/local/gcc/bin/g++")

include(${CMAKE_CURRENT_LIST_DIR}/build_options.cmake)
message("include(${CMAKE_CURRENT_LIST_DIR}/build_options.cmake) ")