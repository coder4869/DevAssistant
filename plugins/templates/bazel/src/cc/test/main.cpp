// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include <stdio.h>

// #include <spdlog/spdlog.h>

#include "src/cc/math.h"
#include "src/cc/perf/perf_monitor.h"

int main(int argc, char **argv) {
    // spdlog::info("Welcome to spdlog!");

    printf("cc demo %s:  1 + 2 = %d \n", __FUNCTION__, add(1, 2));
    PerfMonitor perf;
    auto info = perf.GetPerfInfo();
    perf.PrintPerf(info);
    
    return 0;
}