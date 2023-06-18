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
#include "../utils/CKString.h"

#ifdef WIN
#	include <windows.h>
#endif // WIN

/// @param name upper-case is required!
std::string CKSystemEnv::GetEnv(const char* name)
{
#ifdef WIN
	// https://www.orcode.com/question/1012464_k5c59b.html
	const DWORD buf_size = 4096;
	LPTSTR lp_buf = new TCHAR[buf_size];
	const DWORD var_size = GetEnvironmentVariable(name, lp_buf, buf_size);
	if (var_size == 0) {
		DWORD err = GetLastError();
		std::cout << __FUNCTION__ << "01: Error = " << err << std::endl;
		return "";
	}
	else if (var_size > buf_size) // buf_size not enough
	{
		if (lp_buf) {
			delete[] lp_buf;
		}

		lp_buf = new TCHAR[var_size];
		const DWORD new_size = GetEnvironmentVariable(name, lp_buf, var_size);
		if (new_size == 0 || new_size > var_size) {
			DWORD err = GetLastError();
			std::cout << __FUNCTION__ << "02: Error = " << err << std::endl;
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
std::string CKSystemEnv::GetPathEnv()
{
	return GetEnv("PATH");
}

/// @brief Split Env Value By ";" and remove repeated
/// @param name upper-case is required!
std::set<std::string> CKSystemEnv::SplitEnvValue(const char* name)
{
	std::string env_value = GetEnv(name);
	return CKString::SplitStringToSet(env_value, ';');
}

/// @brief Get PATH Env Value and Split to items by SplitEnvValue();
std::set<std::string> CKSystemEnv::GetPathEnvItems()
{
	auto path_set = SplitEnvValue("PATH");
	return path_set;
}

/// @brief Check Env Key-Value
bool CKSystemEnv::CheckEnv(const std::string& key, const std::string& value)
{
	if (key.empty() || value.empty()) {
		return false;
	}

	bool has_key = false;
	std::string path = "";
	//std::string pathes = "";

	auto path_set = SplitEnvValue(key.c_str());
	for (auto iter = path_set.begin(); iter != path_set.end(); iter++) {
		if (*iter == value) {
			has_key = true;
			path = *iter;
			break;
		}

		//pathes = pathes + "\n" + iter->c_str();
	}

	return has_key;
}

/// @brief Set Env Key-Value 
bool CKSystemEnv::SetEnv(const std::string& key, const std::string& value)
{
	if (CheckEnv(key, value)) {
		return true;
	}

	// Key-Value Not Exist, add or update
#ifdef WIN
	int ret = SetEnvironmentVariable(key.c_str(), value.c_str());
	if (ret == 0) {
		DWORD err = GetLastError();
		std::cout << __FUNCTION__ << "01: Error = " << err << std::endl;
		return false;
	}
#else
	std::string cfg = key + "=" + value;
	putenv(cfg.c_str());
#endif
	return CheckEnv(key, value);
}
