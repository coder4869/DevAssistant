// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "units_time.h"

#include <time.h>

#if _HAS_CXX11
#include <chrono>
#endif

namespace units::time {

const long day2second = 24 * 60 * 60;

uint64_t now_second() {
#if _HAS_CXX11
    auto tpd = std::chrono::system_clock::now().time_since_epoch();
    return  std::chrono::duration_cast<std::chrono::seconds>(tpd).count();
#else
    timeb t;
    ftime(&t); // Get ms time
    return t.time;
#endif
}

uint64_t now_ms() {
#if _HAS_CXX11
    auto tpd = std::chrono::system_clock::now().time_since_epoch();
    return  std::chrono::duration_cast<std::chrono::microseconds>(tpd).count();
#else
    timeb t;
    ftime(&t); // Get ms time
    return t.time*1000 + t.millitm;
#endif
}

std::string second_to_string(uint64_t timestamp, const char* format) {
    time_t tim = (time_t)timestamp;
    struct tm t = *localtime(&tim);
    char tim_str[100];
    std::string tim_fmt;
    // format: "%Y%m%d-%H%M%S" "%Y-%m-%d %H:%M:%S"
    strftime(tim_str, sizeof(tim_str), format, &t);
    tim_fmt = tim_str;
    return tim_fmt;
}

}
