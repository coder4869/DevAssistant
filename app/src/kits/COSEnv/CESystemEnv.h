// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// GetEnvVar: https://www.delftstack.com/zh/howto/cpp/cpp-get-environment-variables/

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <iostream>
#include <string>
#include <set>
#include <cstdlib> // GetEnv putenv

#include "COSEnvDef.h"

NS_CE_BEGIN
extern const std::string OS_NAME;

/// @note Use "\\" as path split character for windows !!!

//class COSEnv_CLASS SystemEnv {
class SystemEnv {
	public:
	/// @param name upper-case is required!
	static std::string GetEnv(const char* name);

	/// @brief Get Env PATH
	static std::string GetPathEnv();

	/// @brief Split Env Value By ";" and remove repeated
	/// @param name upper-case is required!
	static std::set<std::string> SplitEnvValue(const char* name);

	/// @brief Query Env Value and Split to items by SplitEnvValue();
	/// @param env_key	env key value to query
	/// @param soft_key	soft key to search in env_key's value, default is ""
	/// @return Env's sub-item values that contains soft_key, all for soft_key == "".
	static std::set<std::string> GetEnvItems(const char* env_key = "PATH", const char* soft_key = "");

	/// @brief Check Env Key-Value 
	static bool CheckEnv(const std::string& key, const std::string& value);

	/// @brief Set Env Key-Value 
	static bool SetEnv(const std::string& key, const std::string& value);
};
NS_CE_END
