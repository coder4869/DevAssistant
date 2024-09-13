// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef __PATH_UTIL_H__
#define __PATH_UTIL_H__

#include <string>

#define MAX_PATH 4096

namespace utils::path {
extern std::string absolute_path(const std::string &relative_path);

}

#endif //__PATH_UTIL_H__
