// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// Right Action: https://www.cnblogs.com/pengsn/p/13563551.html
// Right Action: https://zhuanlan.zhihu.com/p/369716586
// https://blog.csdn.net/m0_43605481/article/details/121616732

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>

#include "QtEnvKitDef.h"

NS_QEK_BEGIN

class BuildScript {
public:
	static BuildScript* GetInstance();

	BuildScript() {}
	~BuildScript() {}

	/// @brief Update run_win.bat / run_arm.sh / run_unix.sh
	int FixBuildScript(const std::string& script_path);
	int FixBuildScripts(const std::string& proj_path);

	/// @brief Update script file for adapt develop env. 
	/// @param script_path	script file path. File can be : run_win.bat / run_arm.sh / run_unix.sh
	/// @note				script contains install path of develop soft: VS, Qt, CMake, python.
	/// @param err_msg		error message for false, fixed build script for succeed !
	bool Update(const std::string& script_path, std::string& err_msg);

	/// @brief Fix Microsoft Visual Studio Install Path
	/// @param err_msg		error message
	/// return 0-succeed, 1-error
	int CheckVSEnv(std::string& script_data, std::string& err_msg);

	/// @brief Check soft From key(env_var)
	/// @param key		env var key
	/// @param soft		target soft to check in key queryed env var.
	/// @param out_val	check result for return is 0, error code for return not 0
	/// return 0-succeed, 1-error
	int CheckEnvVarSoft(const std::string& key, const std::string& soft, std::string& out_val);

};

NS_QEK_END
