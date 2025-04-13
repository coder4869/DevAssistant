// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "DABuildScript.h"

#include <CUtils/CUString.h>
#include <CUtils/CUFile.h>
#include <COSEnv/CERegedit.h>
#include <COSEnv/CESystemEnv.h>

#if WIN
#	include <windows.h>
#endif

#include <QMessageBox>
#include <CUtils/logger.h>
#define LOG_TAG "TAG_BuildScript"

NS_QEK_BEGIN

static BuildScript* instance = nullptr;
BuildScript* BuildScript::GetInstance()
{
	if (!instance) {
		instance = new BuildScript();
	}
	return instance;
}

int BuildScript::FixBuildScript(const std::string& script_path) {
	std::string err_msg = "";
	bool ret = Update(script_path, err_msg);

	if (ret) {
		CU::File::SaveFileString(script_path, err_msg);
		std::string info = " Fix BuildScript " + script_path + " Succeed: \n" + err_msg;
		LOGI("info = %s", info.c_str());
		QMessageBox::information(NULL, QStringLiteral("FixBuildScript"), QString::fromStdString(info));
		return 0;
	}

	std::string info = " Fix BuildScript " + script_path + " Failed: \n" + err_msg;
	LOGI("info = %s", info.c_str());
	QMessageBox::critical(NULL, QStringLiteral("FixBuildScript"), QString::fromStdString(info));
	return 1;
}

int BuildScript::FixBuildScripts(const std::string& proj_path)
{
	std::string err_msg = "", err_msg_all = "";

	std::string script_path = proj_path + "/run_win.bat";
	bool ret = Update(script_path, err_msg);
	if (ret) { 
		CU::File::SaveFileString(script_path, err_msg); // err_msg is updated file data
		LOGI("Update %s Succeed! Saved scipts:\n%s", script_path.c_str(), err_msg.c_str());
	} else {
		err_msg_all += err_msg;
	}

	script_path = proj_path + "/run_unix.sh";
	ret = Update(script_path, err_msg);
	if (ret) {
		CU::File::SaveFileString(script_path, err_msg); // err_msg is updated file data
		LOGI("Update %s Succeed! Saved scipts:\n%s", script_path.c_str(), err_msg.c_str());
	} else {
		err_msg_all += err_msg;
	}

	script_path = proj_path + "/run_ios.sh";
	ret = Update(script_path, err_msg);
	if (ret) { 
		CU::File::SaveFileString(script_path, err_msg); // err_msg is updated file data
		LOGI("Update %s Succeed! Saved scipts:\n%s", script_path.c_str(), err_msg.c_str());
	} else {
		err_msg_all += err_msg;
	}

	script_path = proj_path + "/run_android.sh";
	ret = Update(script_path, err_msg);
	if (ret) {
		CU::File::SaveFileString(script_path, err_msg); // err_msg is updated file data
		LOGI("Update %s Succeed! Saved scipts:\n%s", script_path.c_str(), err_msg.c_str());
	} else {
		err_msg_all += err_msg;
	}
	
	script_path = proj_path + "/run_android.bat";
	ret = Update(script_path, err_msg);
	if (ret) {
		CU::File::SaveFileString(script_path, err_msg); // err_msg is updated file data
		LOGI("Update %s Succeed! Saved scipts:\n%s", script_path.c_str(), err_msg.c_str());
	} else {
		err_msg_all += err_msg;
	}

	if (err_msg_all.empty()) {
		return 0;
	}
	std::string msg = "Update scripts failed: %s" + err_msg_all;
	LOGI("%s", msg.c_str());
	QMessageBox::critical(NULL, QStringLiteral("FixBuildScripts"), QString::fromStdString(msg));
	return 1;
}

// TODO:: finish scripts
bool BuildScript::Update(const std::string& script_path, std::string& err_msg)
{
	if (script_path.find("run_win.bat") != std::string::npos) {
		std::string file_data = "";
		if (CU::File::LoadFileString(script_path, file_data)) {
			err_msg = script_path + " Open Failed !";
			return false;
		}

		//// Check VS
		//if (CheckVSEnv(file_data, err_msg)) {
		//	return false;
		//}
		
		// Check QT_HOME
		std::string qt_env;
		if (CheckEnvVarSoft("QT_HOME", "Qt", qt_env)) {
			err_msg = "QT_HOME Check Failed " + qt_env;
			return false;
		}
		err_msg = file_data;
		return true;

	} else if (script_path.find("run_unix.sh") != std::string::npos) {
		std::string file_data = "";
		if (CU::File::LoadFileString(script_path, file_data)) {
			err_msg = script_path + " Open Failed !";
			return false;
		}
		err_msg = file_data;
		return true;
	} else if (script_path.find("run_ios.sh") != std::string::npos) {
		std::string file_data = "";
		if (CU::File::LoadFileString(script_path, file_data)) {
			err_msg = script_path + " Open Failed !";
			return false;
		}
		err_msg = file_data;
		return true;
	} else if (script_path.find("run_android.sh") != std::string::npos) {
		std::string file_data = "";
		if (CU::File::LoadFileString(script_path, file_data)) {
			err_msg = script_path + " Open Failed !";
			return false;
		}
		err_msg = file_data;
		return true;
	} else if (script_path.find("run_android.bat") != std::string::npos) {
		std::string file_data = "";
		if (CU::File::LoadFileString(script_path, file_data)) {
			err_msg = script_path + " Open Failed !";
			return false;
		}
		err_msg = file_data;
		return true;
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
