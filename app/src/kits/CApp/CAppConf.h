// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// https://www.delftstack.com/zh/howto/cpp/cpp-get-environment-variables/

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>
#include <map>

#include "CAppDef.h"

//class CAPP_CLASS CKAppConf
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

