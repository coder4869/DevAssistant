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

#include "CodingTools.h"

#include <iostream>

#include <CUtils/logger.h>
#include <COSEnv/CERegedit.h>
#include <COSEnv/CESystemEnv.h>
#include <COSEnv/CEAppLoader.h>

#define LOG_TAG "TAG_COSEnv"

//NS_DE_BEGIN
#if WIN
	const std::string CMAKE_REG = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Kitware\\CMake\\InstallDir";
#else
	const std::string CMAKE_REG = "";
#endif // WIN

std::map<std::string, CodingTool::SoftInfo> CodingTool::GetSoftInfos()
{
    std::map<std::string, CodingTool::SoftInfo>  soft_infos;
    soft_infos["CMake"] = {CMAKE_REG, GetRootDir("CMake", CMAKE_REG)};
    return soft_infos;
}

std::string CodingTool::GetRootDir(const std::string &soft, const std::string &search_key) {
	auto list = CE::SystemEnv::GetEnvItems("PATH", soft.c_str());
	if (list.size() > 0) {
		return *list.begin();
	}

	bool is_dir = false;
	std::string dir = CE::Regedit::GetRegValue(search_key, is_dir);
    if (dir.empty()) {
        std::string app_path;
        if (CE::AppLoader::GetAppInstallPath(soft, app_path)) {
            dir = app_path;
        }
    }
    return dir;
}

std::string CodingTool::CheckEnv()
{
	// Check Install Root Dir
	auto root_dir = CodingTool::GetRootDir("CMake", CMAKE_REG);
	if (root_dir.empty()) {
        LOGE("Error: APP Not Installed !");
		return "Error: APP Not Installed !";
	}

	// Add APP bin_dir to PATH
	auto bin_dir = root_dir + "bin";
	if (!CE::SystemEnv::CheckEnv("PATH", bin_dir)) {
		CE::SystemEnv::SetEnv("PATH", bin_dir);
	}

	// Check pkg-config

	return "Succeed: Use Install Dir [" + root_dir + "] !";
}

//NS_DE_END
