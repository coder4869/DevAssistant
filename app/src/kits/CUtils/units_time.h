// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef __UNITS_TIME_H__
#define __UNITS_TIME_H__

#include <stdint.h>
#include <string>

namespace units::time {
extern const long day2second;
extern uint64_t now_second();
extern uint64_t now_ms();
/// @breif second to string time. e.g. 1699158041 to 2023-11-05 12:20:41
/// @param timestamp    input timestamp in second. e.g. 1699158041
/// @param format           output date format. supports:
///        YYYY-MM-DD HH:mm:ss        YYYYMMDD-HHmmss
/// @return timestamp in target fmt.
extern std::string second_to_string(uint64_t timestamp, const char* format);

}

#endif //__UNITS_TIME_H__
