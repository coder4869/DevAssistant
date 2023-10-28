// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
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

#include "CAppConf.h"

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

	return root_dir_ + "/" + iter->second;
}

std::string CKAppConf::GetRelativePath(const std::string& key, const std::string& path)
{
	if (SetRelativePath(key, path)) {
		return GetRelativePath(key);
	}
	return "";
}
