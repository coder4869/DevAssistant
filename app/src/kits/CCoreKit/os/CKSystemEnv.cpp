// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "CKSystemEnv.h"

#include <iostream>
#include <fstream>

#include <CCoreKit/log/CKLog.h>
#include <CCoreKit/utils/CKString.h>
#include <CCoreKit/os/CKRegisterTable.h>

#ifdef WIN
#	include <windows.h>
#endif // WIN

namespace CK {

/// @param name upper-case is required!
std::string SystemEnv::GetEnv(const char* name)
{
#ifdef WIN
	// https://www.orcode.com/question/1012464_k5c59b.html
	const DWORD buf_size = 4096;
	LPTSTR lp_buf = new TCHAR[buf_size];
	const DWORD var_size = GetEnvironmentVariable(name, lp_buf, buf_size);	// GET System Environment Variable
	if (var_size == 0) {
		bool is_dir = false;
		const std::string user_env = RegisterTable::GetRegValue("HKEY_CURRENT_USER\\Environment\\" + std::string(name), is_dir); // GET USER Environment Variable
		if (!user_env.empty()) {
			return user_env;
		}
		DWORD err = GetLastError();
		LOG_ERR << __FUNCTION__ << "01: Error = " << err << std::endl;
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
			LOG_ERR << __FUNCTION__ << "02: Error = " << err << std::endl;
			return "";
		}

		return std::string(lp_buf, new_size);
	}
	return std::string(lp_buf, var_size);
#else
	const char* val = std::getenv(name);
	std::string env_var(val ? "" : std::string(val));
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
	return String::SplitStringToSet(env_value, ";");
}

/// @brief Get PATH Env Value and Split to items by SplitEnvValue();
std::set<std::string> SystemEnv::GetPathEnvItems()
{
	auto path_set = SplitEnvValue("PATH");
	return path_set;
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
	//LOG_INFO << pathes << std::endl;

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
#ifdef WIN
	std::string cmd = "SETX " + key + " " + "\"" + new_val;
	int ret = system(cmd.c_str());
	if (ret != 0) {
		//DWORD err = GetLastError();
		//LOG_ERR << "01: Error = " << err << std::endl;
		return false;
	}
#else
	std::string cfg = key + "=" + value;
	putenv(cfg.c_str());
#endif
	return CheckEnv(key, new_val);
}

} //namespace CK
