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

#include "DABuildScript.h"

#include <CUtils/CUString.h>
#include <CUtils/CUFile.h>
#include <COSEnv/CERegedit.h>
#include <COSEnv/CESystemEnv.h>

#ifdef WIN
#	include <windows.h>
#endif

#include <CLog/CLLog.h>

NS_QEK_BEGIN

bool BuildScript::Update(const std::string& script_path, std::string& err_msg)
{
	if (script_path.find("run_win.bat")) {
		std::string file_data = "";
		if (CU::File::LoadFileString(script_path, file_data)) {
			err_msg = script_path + " Open Failed !";
			return false;
		}

		// Check VS
		if (CheckVSEnv(file_data, err_msg)) {
			return false;
		}
		
		// Check QT_HOME
		std::string qt_env;
		if (CheckEnvVarSoft("QT_HOME", "Qt", qt_env)) {
			err_msg = "QT_HOME Check Failed " + qt_env;
			return false;
		}
		err_msg = file_data;
		return true;

	} else if (script_path.find("run_unix.sh")) {

	} else if (script_path.find("run_arm.sh")) {

	}
	err_msg = script_path + " not found !";
	return false;
}

int BuildScript::CheckVSEnv(std::string &script_data, std::string& err_msg)
{
	const std::string soft_vs = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\devenv.exe";
	const std::string vs_from = "\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Professional\\Common7\\IDE\\devenv.exe\"";
	bool is_dir = false;
	const std::string vs_to = CE::Regedit::GetRegValue(soft_vs, is_dir);
	if (vs_to.empty()) {
		err_msg = "Microsoft Visual Studio May Be Not Installed !";
		return 1;
	}
	auto pos = vs_to.find("2022");
	if (pos != std::string::npos) {
		CU::String::Replace(script_data, vs_from, vs_to);
		CU::String::Replace(script_data, "Visual Studio 16 2019", "Visual Studio 17 2022");
	}

	return 0;
}

int BuildScript::CheckEnvVarSoft(const std::string& key, const std::string& soft, std::string& out_val)
{
	bool has_key = false;
	std::string pathes = "";

	auto path_set = CE::SystemEnv::SplitEnvValue(key.c_str());
	for (auto iter = path_set.begin(); iter != path_set.end(); iter++) {
		std::string tmp = *iter;
		if (tmp.find(soft) != std::string::npos) {
			has_key = true;
			out_val = tmp;
			break;
		}

		pathes = pathes + "\n" + iter->c_str();
	}

	if (!has_key) {
		out_val = soft + " in EnvVar " + key + " Not Found !";
		return 1;
	}
	return 0;
}

NS_QEK_END
