#include "CKSystemEnv.h"

#include <iostream>

#ifdef WIN32
#	include <windows.h>
#endif // WIN32


/// https ://www.orcode.com/question/1012464_k5c59b.html
/// @param name upper-case is required!
std::string CKSystemEnv::GetEnv(const char* name)
{
#ifdef WIN32
	//https ://www.orcode.com/question/1012464_k5c59b.html
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
	std::set<std::string> values;
	std::string env_value = GetEnv(name);
	if (!env_value.empty()) {
		// Split Env Value By ";"
		std::string sub_str;
		char tag = ';';

		for (size_t idx = 0; idx < env_value.size(); idx++) {
			if (tag == env_value[idx]) // Finish once
			{
				if (!sub_str.empty()) {
					values.insert(sub_str);
					sub_str.clear();
				}
			}
			else // Finding next tag continue
			{
				sub_str.push_back(env_value[idx]);
			}
		}

		if (!sub_str.empty()) {
			values.insert(sub_str);
			sub_str.clear();
		}
	}

	//for (auto item = values.begin(); item != values.end(); item++) {
	//	std::cout << __FUNCTION__ << item->c_str() << std::endl;
	//}

	return values;
}

/// @brief Get PATH Env Value and Split to items by SplitEnvValue();
std::set<std::string> CKSystemEnv::GetPathEnvItems()
{
	auto path_set = SplitEnvValue("PATH");
	return path_set;
}
