// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef __CU_PERF_MONITOR_H__
#define __CU_PERF_MONITOR_H__

#include "CUtilsDef.h"

#include <chrono>
#include <string>

#include <iostream>
#include <CUtils/logger.h>

NS_CU_BEGIN

template <typename Func>
void measure_time(const std::string & msg, Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func(); 
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    LOGI("%s : msg = %s, time = %d s", __FUNCTION__, msg.c_str(), elapsed.count());
}

NS_CU_END

#endif // __CU_PERF_MONITOR_H__
