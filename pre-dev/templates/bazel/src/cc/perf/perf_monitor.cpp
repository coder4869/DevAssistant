// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "src/cc/perf/perf_monitor.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/syscall.h>

PerfInfo PerfMonitor::GetPerfInfo() {
    PerfInfo info;
    info.ppid = getppid();
    info.pid = getpid();
    info.tid = syscall(SYS_gettid);
}

void PerfMonitor::PrintPerf(const PerfInfo & info) {
    printf("ppid = %lld, pid = %lld, tid = %lld\n", info.ppid, info.pid, info.tid);
}

