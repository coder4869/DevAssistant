// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "path_util.h"

#include <limits.h>
#include <filesystem>
#include <chrono>

namespace utils::path {

std::string absolute_path(const std::string &relative_path) {
    std::filesystem::path tmp_path = relative_path;
#if WIN
    char abs_path[MAX_PATH] = {0};
    _fullpath(abs_path, relative_path.c_str(), MAX_PATH);
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

static uint64_t file_last_write_ms(std::filesystem::path file_path) {
    auto last_write_time = std::filesystem::last_write_time(file_path);
    return std::chrono::duration_cast<std::chrono::seconds>(last_write_time.time_since_epoch()).count();
}

}
