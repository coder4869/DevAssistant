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

// GetEnvVar: https://www.delftstack.com/zh/howto/cpp/cpp-get-environment-variables/

#pragma once

#include <CLog/CKDefines.h>

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

	/// @brief Get PATH Env Value and Split to items by SplitEnvValue();
	static std::set<std::string> GetPathEnvItems();

	/// @brief Check Env Key-Value 
	static bool CheckEnv(const std::string& key, const std::string& value);

	/// @brief Set Env Key-Value 
	static bool SetEnv(const std::string& key, const std::string& value);
};
NS_CE_END
