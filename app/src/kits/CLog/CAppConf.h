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

// https://www.delftstack.com/zh/howto/cpp/cpp-get-environment-variables/

#pragma once

#include "CKDefines.h"

#include <string>
#include <map>

#include "CLogDef.h"

//class CLOG_CLASS CKAppConf
class CKAppConf
{
public:
	static CKAppConf *GetInstance();

	/// @param	root	root dir path, path component separator is '/'
	/// @return false for empty root
	bool SetRootDir(const std::string& root);

	/// @return root dir path, path component separator is '\\' for windows, otherwhise is '/' 
	std::string GetRootDir();

	/// @param	key		key for relative path
	/// @param	path	root_dir_ based relative file/dir path. path component separator is '/'
	bool SetRelativePath(const std::string& key, const std::string& path);

	/// @param	key		key for relative path
	/// @return root_dir_ append relative file/dir path.
	std::string GetRelativePath(const std::string& key = "");

	/// @brief	Call SetRelativePath() first, and GetRelativePath() then
	/// @param	key		key for relative path
	/// @param	path	root_dir_ based relative file/dir path. path component separator is '/'
	/// @return root_dir_ append relative file/dir path.
	std::string GetRelativePath(const std::string& key, const std::string& path);

protected:
	std::string root_dir_;
	std::map<std::string, std::string> relative_path_map_;
};

