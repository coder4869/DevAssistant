// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#pragma once

#include <cstdio>
#include <cstring>
#include <string>
#include <mutex>

//#define DEBUG 1

#ifdef __GNUC__
#   define LOG_CHECK_PRINTF(m, n) __attribute__((format(printf, m, n)))
#else
#   define LOG_CHECK_PRINTF(m, n)
#endif

#ifndef LOG_TAG
#   define LOG_TAG (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifndef LOG_BUF_SIZE
#if defined(ANDROID) || defined(__ANDROID__)
#   define LOG_BUF_SIZE 4096
#else
#   define LOG_BUF_SIZE (1024*1024)
#endif
#endif

typedef enum log_level {
    LOG_VERBOSE,
    LOG_DEBUG,  // default for DEBUG mode
    LOG_INFO,   // default for non-DEBUG mode
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL   // critical for DEBUG mode, err for non-DEBUG mode
} log_level_t;

class Logger {
public:
    static void SetShowLevel(log_level_t level);
    /// @param log_dir write log to console only for log_dir==""; wirte to console and log_dir/Logger-date.log file for log_dir!=""
    static void SetLogWriter(const std::string &log_dir = "", int flush_interval_ms = 5);

    // this arg is num1 so 4, 5
    static uint32_t Log(const char* tag, log_level_t level, const char* fmt, ...) LOG_CHECK_PRINTF(3, 4);
    static uint32_t LogImpl(const char* tag, log_level_t level, const char* buf);
    static void EnableDebugToInfo(bool enable) { debug_2_info_ = enable; }
    
private:
    static void LogToConsole(const char* tag, log_level_t level, const char* buf);
    static std::string UpdateLogFileName();
    static bool CheckLogDir(const std::string &log_dir);
    
private:
    static log_level_t show_level_;
    static bool debug_2_info_;
    static std::string log_dir_;
    static std::recursive_mutex mutex_;
};

#define LOGV(...) (Logger::Log(LOG_TAG, LOG_VERBOSE, __VA_ARGS__))
#define LOGD(...) (Logger::Log(LOG_TAG, LOG_DEBUG, __VA_ARGS__))
#define LOGI(...) (Logger::Log(LOG_TAG, LOG_INFO, __VA_ARGS__))
#define LOGW(...) (Logger::Log(LOG_TAG, LOG_WARN, __VA_ARGS__))
#define LOGE(...) (Logger::Log(LOG_TAG, LOG_ERROR, __VA_ARGS__))
#define LOGF(...) (Logger::Log(LOG_TAG, LOG_FATAL, __VA_ARGS__))
