// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CESystemEnv.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#if !defined(WIN)
#	include <unistd.h>
#endif

#include <CUtils/logger.h>
#include <CUtils/CUString.h>
#include <COSEnv/CERegedit.h>

#define LOG_TAG "TAG_COSEnv"

#if WIN
#	include <windows.h>
#endif // WIN

NS_CE_BEGIN

#if WIN
const std::string OS_NAME = "Windows";
const std::string ENV_PATH_SPLIT = ";";
#elif defined(MAC) || defined(OSX)
const std::string OS_NAME = "Darwin";
const std::string ENV_PATH_SPLIT = ":";
#else
const std::string OS_NAME = "Linux";
const std::string ENV_PATH_SPLIT = ":";
#endif // WIN

/// @param name upper-case is required!
std::string SystemEnv::GetEnv(const char* name)
{
#if WIN
	// https://www.orcode.com/question/1012464_k5c59b.html
	const DWORD buf_size = 4096;
	LPTSTR lp_buf = new TCHAR[buf_size];
	const DWORD var_size = GetEnvironmentVariable(name, lp_buf, buf_size);	// GET System Environment Variable
	if (var_size == 0) {
		bool is_dir = false;
		const std::string user_env = Regedit::GetRegValue("HKEY_CURRENT_USER\\Environment\\" + std::string(name), is_dir); // GET USER Environment Variable
		if (!user_env.empty()) {
			return user_env;
		}
		DWORD err = GetLastError();
		LOGE("01: Error = %d", err);
		return "";
	}
	else if (var_size > buf_size) // buf_size not enough
	{
		if (lp_buf) {
			delete[] lp_buf;
		}

		lp_buf = new TCHAR[var_size];
		const DWORD new_size = GetEnvironmentVariable(name, lp_buf, var_size); // GET System Environment Variable
		if (new_size == 0 || new_size > var_size) {
			DWORD err = GetLastError();
            LOGE("02: Error = %d", err);
			return "";
		}

		return std::string(lp_buf, new_size);
	}
	return std::string(lp_buf, var_size);
#else
    char* uname = getlogin();
    uid_t uid = geteuid();
    
	const char* val = std::getenv(name);
	std::string env_var(val == NULL ? "" : std::string(val));
    LOGI("current user = %s, uid = %d, env_name = %s, env_var = %s",
         uname, uid, name, env_var.c_str());
	return env_var;
#endif
}

/// @brief Get Env PATH
std::string SystemEnv::GetPathEnv()
{
	return GetEnv("PATH");
}

/// @brief Split Env Value By ";" and remove repeated
/// @param name upper-case is required!
std::set<std::string> SystemEnv::SplitEnvValue(const char* name)
{
	std::string env_value = GetEnv(name);
	std::set<std::string> values;
	CU::String::SplitStringToSet(env_value, ENV_PATH_SPLIT, values);
	return values;
}

/// @brief Query Env Value and Split to items by SplitEnvValue();
std::set<std::string> SystemEnv::GetEnvItems(const char* env_key, const char* soft_key)
{
	auto path_set = SplitEnvValue(env_key);
	if (std::string(soft_key) == "") {
		return path_set;
	}
	std::set<std::string> list;
	for (auto it : path_set) {
		if (it.find(soft_key) != std::string::npos) {
			list.insert(it);
		}
	}
	return list;
}

/// @brief Check Env Key-Value
bool SystemEnv::CheckEnv(const std::string& key, const std::string& value)
{
	if (key.empty() || value.empty()) {
		return false;
	}

	bool has_key = false;
	std::string path = "";
	//std::string pathes = "";

	auto path_set = SplitEnvValue(key.c_str());
	for (auto iter = path_set.begin(); iter != path_set.end(); iter++) {
		if ((*iter).size() == value.size()) {
			if ((*iter) == value) {
				has_key = true;
				path = *iter;
				break;
			}
		}
		//pathes = pathes + "\n" + iter->c_str();
	}
	//LOGI("pathes = %s", pathes.c_str());

	return has_key;
}

/// @brief Set Env Key-Value 
bool SystemEnv::SetEnv(const std::string& key, const std::string& value)
{
	if (CheckEnv(key, value)) {
		return true;
	}

	// Key-Value Not Exist, add or update
	std::string old_val = GetEnv(key.c_str());
	const std::string new_val = old_val.empty() ? value : old_val.append(";").append(value);
#if WIN
	std::string cmd = "SETX " + key + " " + "\"" + new_val;
	int ret = system(cmd.c_str());
	if (ret != 0) {
		//DWORD err = GetLastError();
        //LOGE("01: Error = %d", err);
		return false;
	}
#else
	std::string cfg = key + "=" + value;
#if LIUNX
//    TODO:: adapt darwin
	putenv(cfg.c_str());
#endif
#endif
	return CheckEnv(key, new_val);
}

NS_CE_END
