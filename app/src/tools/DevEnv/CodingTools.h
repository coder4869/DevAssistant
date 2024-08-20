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

#ifndef DE_CODINGTOOLS_H
#define DE_CODINGTOOLS_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>
#include <map>

#include "DevEnvDef.h"

//NS_DE_BEGIN
namespace CodingTool {

    struct SoftInfo {
        std::string search_key = "";
        std::string install_path = "";
    };

    /// @return <soft, <search-key, install—path>>
    std::map<std::string, SoftInfo> GetSoftInfos();

	/// @brief Get APP Query Key. RegVar(Windows) or EnvPath
	std::string GetQueryKey();

	/// @brief Get APP Installed Path 
	std::string GetRootDir(const std::string &soft, const std::string &search_key);

	/// @brief Check APP Env. e.g. Install Path Exist or not in PATH EnvVar, Pkg-config Exist or Not.
	std::string CheckEnv();

} //namespace CodingTool
//NS_DE_BEGIN

#endif // DE_CODINGTOOLS_H
