// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "path_util.h"

#include <limits.h>
#include <filesystem>

namespace utils::path {

std::string absolute_path(const std::string &relative_path) {
    std::filesystem::path tmp_path = relative_path;
#ifdef WIN
    char abs_path[PATH_MAX] = {0};
    _fullpath(absPath, relative_path.c_str(), abs_path);
    return abs_path;

#else
    std::string abs_path;
    if (tmp_path.string().front() == '~') {
        std::string home_dir = std::getenv("HOME");
        abs_path = home_dir + tmp_path.string().substr(1);
    }
    return std::filesystem::canonical(abs_path);
#endif
}

}
