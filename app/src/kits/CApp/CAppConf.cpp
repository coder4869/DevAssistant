// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CAppConf.h"

#include <algorithm>

static CKAppConf* instance = nullptr;

CKAppConf* CKAppConf::GetInstance()
{
	if (!instance) {
		instance = new CKAppConf();
	}
	return instance;
}

bool CKAppConf::SetRootDir(const std::string &root)
{
	if (root.empty()) {
		return false;
	}

	root_dir_ = root[root.size()-1] == '/' ? root : root + '/';
	return true;
}

std::string CKAppConf::GetRootDir() { 
	auto ret = root_dir_;
#ifdef WIN
	std::replace(ret.begin(), ret.end(), '/', '\\');
#endif // WIN
	return ret; 
}

bool CKAppConf::SetRelativePath(const std::string& key, const std::string& path)
{
	if (key.empty() || path.empty()) {
		return false;
	}

	relative_path_map_[key] = path;
	return true;
}

std::string CKAppConf::GetRelativePath(const std::string& key)
{
	auto iter = relative_path_map_.find(key);
	if (iter == relative_path_map_.end()) {
		return "";
	}

	auto ret = root_dir_ + "/" + iter->second;

#ifdef WIN
	std::replace(ret.begin(), ret.end(), '/', '\\');
#endif // WIN

	return ret;
}

std::string CKAppConf::GetRelativePath(const std::string& key, const std::string& path)
{
	if (SetRelativePath(key, path)) {
		return GetRelativePath(key);
	}
	return "";
}
