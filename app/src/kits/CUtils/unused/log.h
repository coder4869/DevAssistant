// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#pragma once

// https://blog.csdn.net/ouyang_peng/article/details/124703411

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <time.h>

#ifdef WIN
#include <direct.h>
#endif // WIN

static std::ofstream g_log;
static bool g_log_open = false;

static void log_open() {
#ifdef WIN
	_mkdir("logs");
#else
	// TDDO :: Linux mkdir
#endif
	if (!g_log_open) {
		timeb tmb;
		ftime(&tmb); // Get ms time
		char tim_str[100];
		struct tm t = *localtime(&tmb.time);
		strftime(tim_str, sizeof(tim_str), "%Y%m%d-%H%M%S", &t);
		char log_name[80];
		sprintf(log_name, "logs/log-%s.log", tim_str); // std::cerr
		g_log.open(log_name, std::ofstream::app);
		g_log_open = true;
	}
}

static void log_close() {
	if (g_log_open) {
		g_log.close();
		g_log_open = false;
	}
}

#define LOG_BASE \
		log_open(); \
		g_log << "[ "<< __FILE__ << " : " << __LINE__ << " ]"

#ifdef DEBUG
#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
// Windows
#	define LOG_INFO LOG_BASE << " INFO: " << __FUNCTION__ << " "
#	define LOG_WARN LOG_BASE << " WARN: " << __FUNCTION__ << " "
#	define LOG_ERR	LOG_BASE << " ERROR: " << __FUNCTION__ << " "

#	elif (defined __APPLE__) || (defined __MACH__) 
// MAC

#	elif (defined __ANDROID__)
// Android

#	elif (defined __linux__) || (defined __unix__) 
// Linux

#	endif

#else // RELEASE
#	if (defined WIN) || (defined WIN32) || (defined _WIN32) || (defined _WIN64)
// Windows
#	define LOG_INFO LOG_BASE << " INFO: " << __FUNCTION__ << " "
#	define LOG_WARN LOG_BASE << " WARN: " << __FUNCTION__ << " "
#	define LOG_ERR	LOG_BASE << " ERROR: " << __FUNCTION__ << " "

#	elif (defined __APPLE__) || (defined __MACH__) 
// MAC
#    define LOG_INFO LOG_BASE << " INFO: " << __FUNCTION__ << " "
#    define LOG_WARN LOG_BASE << " WARN: " << __FUNCTION__ << " "
#    define LOG_ERR  LOG_BASE << " ERROR: " << __FUNCTION__ << " "

#	elif (defined __ANDROID__)
// Android

#	elif (defined __linux__) || (defined __unix__) 
// Linux

#	endif

#endif // DEBUG
