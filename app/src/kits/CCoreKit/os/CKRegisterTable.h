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

// Right Action: https://www.cnblogs.com/pengsn/p/13563551.html
// Right Action: https://zhuanlan.zhihu.com/p/369716586
// Register Table Read-Write : https://www.cnblogs.com/LyShark/p/15019685.html
// Register Table Read-Write : https://blog.csdn.net/xhlzjd/article/details/85250741

#pragma once

#include "CCKDefines.h"

#include <string>

namespace CK {

namespace RegisterTable {
	/// @param key e.g. "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\devenv.exe"
	std::string GetRegValue(const std::string &key);

	/// @param hkey HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_USERS, HKEY_CURRENT_CONFIG
	/// @param reg_path hkey Removed (start without '\'，end with '\'). e.g. 
	///		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\devenv.exe"
	/// @param reg_key key in reg_path. Default is "". e.g. "PackageRepositoryRoot"
	std::string GetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key = "");
	
	/// @param key e.g. "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\devenv.exe"
	/// @param value e.g. "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
	bool SetRegValue(const std::string& key, const std::string& value);

	/// @param hkey HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_USERS, HKEY_CURRENT_CONFIG
	/// @param reg_path hkey Removed (start without '\'，end with '\'). e.g. 
	///		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\devenv.exe"
	/// @param reg_key key in reg_path. Default is "". e.g. "PackageRepositoryRoot"
	/// @param reg_value value for reg_path. e.g. 
	///		"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
	bool SetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key = "",
							const std::string& reg_value = "");
}

} //namespace CK
