// MIT License
//
// Copyright (c) 2021~2023 [coder4869](https://github.com/coder4869)
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
#include <functional>

#include "COSEnvDef.h"

NS_CE_BEGIN
namespace RightAction {
	using CallBack = std::function<void(const std::string &)>;
	enum class Mode : uint8_t {
		ALL_FILES = 0,	// Windows: HKEY_CLASSES_ROOT\*
		FIX_SUFFIX,		// e.g. .bat/.sh . Windows: HKEY_CLASSES_ROOT\.xx
		FOLDER,			// Windows: HKEY_CLASSES_ROOT\Folder
		DIR,			// Windows: HKEY_CLASSES_ROOT\Directory 
		DIR_BACK		// Windows: HKEY_CLASSES_ROOT\Directory\Background
	};

	/// @brief require Admin Authority.
	/// e.g CE::RightAction::AddAction("DevAssist", "PATH/TO/Bat-Update", 
	///									"Tips-Run bat", "Path/to/Icon",
	///									CE::RightAction::Mode::ALL_FILES);
	/// @param key		right action response function Regedit key.
	/// @param action	action file path. e.g. "path/to/run.bat", "path/to/run.exe". 
	///					Use "\\" as path split character for windows !!!
	/// @param tips		Right Action Tips.	
	/// @param icon		Right Action Tips Icon Path.	
	/// @param mode		action type, type define refer to "enum class Mode : uint8_t"
	/// @param suffix	only useful for mode == FIX_SUFFIX. mapping "key-regeditDir"e.g. 
	///					bat-batfile; sh; xls; doc
	/// @return	error code. 0-succeed, 1-param error, 
	///						2-mode invalid, 3-regedit error.
	int AddAction(const std::string &key, const std::string& action,
					const std::string& tips, const std::string& icon,
					Mode mode, const std::string& suffix = "", 
					bool clear_old = false);

	/// @demo DelAction("DevAssist", CE::RightAction::Mode::ALL_FILES);
	/// @demo DelAction("DevAssist", CE::RightAction::Mode::FIX_SUFFIX, "batfile");
	/// @param key		Same to AddAction() Key !!! right action response function Regedit key. 
	///					Use "\\" as path split character for windows !!!
	/// @param mode		Same to AddAction() mode !!! action type, type define refer to "enum class Mode : uint8_t"
	/// @param suffix	only useful for mode == FIX_SUFFIX. mapping "key-regeditDir"e.g. 
	///					bat-batfile; sh; xls; doc
	/// @return	error code. 0-succeed, 1-param error, 
	///						2-mode invalid, 3-regedit error.
	int DelAction(const std::string& key, Mode mode, const std::string& suffix = "");
}

NS_CE_END
