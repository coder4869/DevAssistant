// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
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

// Right Action: https://www.cnblogs.com/pengsn/p/13563551.html
// Right Action: https://zhuanlan.zhihu.com/p/369716586
// https://blog.csdn.net/m0_43605481/article/details/121616732

#pragma once

#include <CLog/CKDefines.h>

#include <string>

#include "QtEnvKitDef.h"

NS_QEK_BEGIN

namespace BuildScript {
	/// @brief Update script file for adapt develop env. 
	/// @param script_path	script file path. File can be : run_win.bat / run_arm.sh / run_unix.sh
	/// @note				script contains install path of develop soft: VS, Qt, CMake, python.
	/// @param err_msg		error message for false, fixed build script for succeed !
	bool Update(const std::string & script_path, std::string & err_msg);

	/// @brief Fix Microsoft Visual Studio Install Path
	/// @param err_msg		error message
	/// return 0-succeed, 1-error
	int CheckVSEnv(std::string& script_data, std::string& err_msg);

	/// @brief Check soft From key(env_var)
	/// @param key		env var key
	/// @param soft		target soft to check in key queryed env var.
	/// @param out_val	check result for return is 0, error code for return not 0
	/// return 0-succeed, 1-error
	int CheckEnvVarSoft(const std::string& key, const std::string& soft, std::string &out_val);

} // namespace BuildScript

NS_QEK_END
