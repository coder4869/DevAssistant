#pragma once

// https://blog.csdn.net/ouyang_peng/article/details/124703411

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

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
		g_log.open("logs/test.log", std::ofstream::app);
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

#	elif (defined __ANDROID__)
// Android

#	elif (defined __linux__) || (defined __unix__) 
// Linux

#	endif

#endif // DEBUG
