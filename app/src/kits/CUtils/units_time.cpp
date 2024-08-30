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

#include "units_time.h"

#include <sys/timeb.h>
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
