// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef __PERF_MONITOR__
#define __PERF_MONITOR__

#include <unistd.h>

struct PerfInfo {
    pid_t ppid;
    pid_t pid;
    pid_t tid;
};

class PerfMonitor {
public:    
    PerfInfo GetPerfInfo();

    void PrintPerf(const PerfInfo & info);
};

#endif // __PERF_MONITOR__