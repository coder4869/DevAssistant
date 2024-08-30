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

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>

#include "COSEnvDef.h"

NS_CE_BEGIN

namespace AppLoader {

    bool GetAppPath(const std::string &bin_path, std::string &output);
    bool GetAppDirPath(const std::string &bin_path, std::string &output);

    /// @brief Get System Installed App Path
    /// @param  app_name   app bin name
    /// @param  output   app_name bin path for return succeed, error message for return false
    /// @return  Query Result.  false for not find app, true for query succed
    bool GetAppInstallPath(const std::string &app_name, std::string &output);

	/// @brief Run Application As Root Authority
	bool RunAsRoot(const std::string &bin_path);

    
	/// @brief Run Application When OS Start
	/// @param app_key		application key. e.g.
    ///     for windows: "DevTool"  ;  for mac "bundle_id"
	/// @param app_path		application path. e.g.
    ///     for windows: "C:\\path\\to\\app\\bin\\DevAssistant.exe" ;  for mac: "/Applications/DevAssistant.app"
	/// @return	Run Result.
	bool RunAsOSStart(const std::string &app_key, const std::string & bin_path);
}

NS_CE_END
