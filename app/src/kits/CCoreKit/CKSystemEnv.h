// https://www.delftstack.com/zh/howto/cpp/cpp-get-environment-variables/

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <cstdlib> // GetEnv

class CKSystemEnv
{
public:
	/// @param name upper-case is required!
	static std::string GetEnv(const char*name);

	/// @brief Get Env PATH
	static std::string GetPathEnv();

	/// @brief Split Env Value By ";" and remove repeated
	/// @param name upper-case is required!
	static std::set<std::string> SplitEnvValue(const char* name);

	/// @brief Get PATH Env Value and Split to items by SplitEnvValue();
	static std::set<std::string> GetPathEnvItems();
};

