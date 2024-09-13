// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

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
	/// @param bin_path		application path. e.g.
    ///     for windows: "C:\\path\\to\\app\\bin\\DevAssistant.exe" ;
    ///     for mac: "/Applications/DevAssistant.app/Contents/MacOS/DevAssistant"
	/// @return	Run Result.
	bool RunAsOSStart(const std::string &app_key, const std::string & bin_path);
}

NS_CE_END
