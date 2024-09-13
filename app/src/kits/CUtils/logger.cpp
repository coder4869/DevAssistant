// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// https://github.com/gabime/spdlog
// https://blog.csdn.net/stallion5632/article/details/139814667

#include "logger.h"

#include <stdarg.h>
#include <chrono>
#if _HAS_CXX17
#include <filesystem> // C++17
#endif

#ifdef WIN
#include <direct.h>
#endif // WIN

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
// #include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <CUtils/units_time.h>

//static const char* log_fmt = "%z %Y-%m-%d %H:%M:%S.%e %P %t %L %v";
static const char* log_fmt = "%Y-%m-%d %H:%M:%S.%e %P %t %L %v";
//static std::shared_ptr<spdlog::logger> console_logger = spdlog::stdout_color_mt("console_logger");
static std::shared_ptr<spdlog::async_logger> log_writer = nullptr;

#if DEBUG
log_level_t Logger::show_level_ = LOG_DEBUG;
#else
log_level_t Logger::show_level_ = LOG_INFO;
#endif

bool Logger::debug_2_info_ = false;
std::string Logger::log_dir_ = "";
std::recursive_mutex Logger::mutex_;

void Logger::SetShowLevel(log_level_t level) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    show_level_ = level;
    spdlog::set_level(spdlog::level::info);
    switch (level) {
        case LOG_DEBUG: spdlog::set_level(spdlog::level::debug);    break;
        case LOG_INFO:  spdlog::set_level(spdlog::level::info);     break;
        case LOG_WARN:  spdlog::set_level(spdlog::level::warn);     break;
        case LOG_ERROR: spdlog::set_level(spdlog::level::err);      break;
        case LOG_FATAL:
#if DEBUG
            spdlog::set_level(spdlog::level::critical); break;
#else
            spdlog::set_level(spdlog::level::err); break;
#endif
        default:
            break;
    }
}

void Logger::SetLogWriter(const std::string &log_dir, int flush_interval_ms) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    
    // max logs number is 8292 in log queue, log print sub-thread number is 8
    spdlog::init_thread_pool(8292, 8);
    auto sink_console = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
    if (CheckLogDir(log_dir)) {
        log_dir_ = log_dir;
        const std::string file_name = log_dir + "/" + UpdateLogFileName();
//        auto sink_file = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_name.c_str());
        // set max keep 5 log files and each log max size 10MB
        auto sink_file = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name.c_str(),
                                                                                10 * 1024 * 1024, 5);
        std::vector<spdlog::sink_ptr> sinks{sink_console, sink_file};
        log_writer = std::make_shared<spdlog::async_logger>("console-file", sinks.begin(), sinks.end(),
                            spdlog::thread_pool(), spdlog::async_overflow_policy::overrun_oldest);
    } else {
        log_dir_ = "";
        log_writer = std::make_shared<spdlog::async_logger>("console-only", sink_console,
                            spdlog::thread_pool(), spdlog::async_overflow_policy::overrun_oldest);
    }
    
    log_writer->set_pattern(log_fmt);
    log_writer->flush_on(spdlog::level::err); // flush when error occurs
    spdlog::flush_every(std::chrono::seconds(flush_interval_ms)); // flush once every 5 seconds
//    spdlog::drop_all();
}

uint32_t Logger::Log(const char* tag, log_level_t level, const char* fmt, ...) {
    std::unique_lock<std::recursive_mutex> lock(mutex_);
    if (debug_2_info_ && level == LOG_DEBUG) {
        level = LOG_INFO;
    }
    if (level < show_level_) {
        return 0;
    }
    
    va_list ap;
    thread_local char buf[LOG_BUF_SIZE];
    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);
    va_end(ap);
    
    return LogImpl(tag, level, buf);
}

uint32_t Logger::LogImpl(const char* tag, log_level_t level, const char* buf) {
    if (log_writer == nullptr) {
        spdlog::set_pattern(log_fmt);
        spdlog::error("Logger not inited! only supports console log ....");
        LogToConsole(tag, level, buf);
        return -1;
    }

    log_writer->set_pattern(log_fmt);
    
    if (level == LOG_FATAL) {
#if DEBUG
        log_writer->critical("{}: {}", tag, buf);
        abort();
#else
        log_writer->error("{}: {}", tag, buf);
#endif
    } else if (level == LOG_ERROR) {
        log_writer->error("{}: {}", tag, buf);
    } else if (level == LOG_WARN) {
        log_writer->warn("{}: {}", tag, buf);
    } else if (level == LOG_INFO) {
        log_writer->info("{}: {}", tag, buf);
    } else if (level == LOG_DEBUG) {
        log_writer->debug("{}: {}", tag, buf);
    } else if (level == LOG_VERBOSE) {
        log_writer->trace("{}: {}", tag, buf);
    } else {
        log_writer->info("{}: {}", tag, buf);
    }
    log_writer->flush();
    return 0;
}

void Logger::LogToConsole(const char* tag, log_level_t level, const char* buf) {
//    spdlog::set_pattern(log_fmt);
    if (level == LOG_FATAL) {
#if DEBUG
        spdlog::critical("{}: {}", tag, buf);
        abort();
#else
        spdlog::error("{}: {}", tag, buf);
#endif
    } else if (level == LOG_ERROR) {
        spdlog::error("{}: {}", tag, buf);
    } else if (level == LOG_WARN) {
        spdlog::warn("{}: {}", tag, buf);
    } else if (level == LOG_INFO) {
        spdlog::info("{}: {}", tag, buf);
    } else if (level == LOG_DEBUG) {
        spdlog::debug("{}: {}", tag, buf);
    } else if (level == LOG_VERBOSE) {
        spdlog::trace("{}: {}", tag, buf);
    } else {
        spdlog::info("{}: {}", tag, buf);
    }
}

std::string Logger::UpdateLogFileName() {
    uint64_t now_time = units::time::now_second();
    std::string time_str = units::time::second_to_string(now_time, "%Y%m%d-%H%M%S");
    char log_name[80];
    sprintf(log_name, "Logger-%s.log", time_str.c_str()); // std::cerr
    return log_name;
}

static int DeleteLogFiles(const std::string& dir_path) {
#if _HAS_CXX17
    if (!std::filesystem::exists(dir_path) || !std::filesystem::is_directory(dir_path)) {
        LOGE("%s : dir %s not exist or not directory !", __FUNCTION__, dir_path.c_str());
        return -1;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".log") {
            auto fsize = std::filesystem::file_size(entry.path()) / 1024;
            auto last_write_time = std::filesystem::last_write_time(entry.path());
            auto last_write_ms = std::chrono::duration_cast<std::chrono::seconds>(last_write_time.time_since_epoch()).count();
            //auto last_write_ms = decltype(last_write_time)::clock::to_time_t(last_write_time);
            // std::cout << "Last modified time: " << std::asctime(std::localtime(&last_write_ms));
            uint64_t current_ms = units::time::now_second();
            if (current_ms - last_write_ms <= units::time::day2second) {
                spdlog::info("log file {} file size {} KB last write time to now {} ms !",
                             entry.path().string().c_str(), fsize, current_ms - last_write_ms);
                continue;
            }
            
            // delete file write last day
            std::error_code ec;
            std::filesystem::remove(entry.path(), ec);
            if (ec) {
                spdlog::error("delete log file {} error {} file size {} KB last write time {} ms !",
                              entry.path().string().c_str(), ec.message(), fsize, last_write_ms);
            } else {
                spdlog::info("delete log file {} succeed file size {} KB last write time {} ms !",
                             entry.path().string().c_str(), fsize, last_write_ms);
            }
        }
    }
    return 0;
#else
    LOGE("%s : Error C++17 Not Support !", __FUNCTION__);
    return -2;
#endif
}

bool Logger::CheckLogDir(const std::string &log_dir) {
    if (log_dir.empty()) {
        return false;
    }
    
#if _HAS_CXX17
    try {
        spdlog::set_pattern(log_fmt);
        if (!std::filesystem::exists(log_dir)) {
            std::filesystem::create_directories(log_dir);
            spdlog::info("create log_dir {} succeed !", log_dir.c_str());
        } else {
            DeleteLogFiles(log_dir);
            spdlog::info("log_dir {} exist !", log_dir.c_str());
        }
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        spdlog::critical("create log_dir {} failed ! {}", log_dir.c_str(), e.what());
#if DEBUG
        abort();
#endif
//        std::cerr << "Create dir failed !" << e.what() << std::endl;
    }
#endif
    return false;
}
