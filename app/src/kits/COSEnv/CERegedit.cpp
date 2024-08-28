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

#include "CERegedit.h"

#include <iostream>

#ifdef WIN
#	include <windows.h>
#endif

#include <CUtils/logger.h>

#define LOG_TAG "TAG_COSEnv"

NS_CE_BEGIN

#ifdef WIN
static HKEY GetRegHKeyRootHandle(const std::string &key) 
{
	HKEY hkey = HKEY_LOCAL_MACHINE;
	if (key == "HKEY_LOCAL_MACHINE") {
		hkey = HKEY_LOCAL_MACHINE;
	}
	else if (key == "HKEY_CLASSES_ROOT") {
		hkey = HKEY_CLASSES_ROOT;
	}
	else if (key == "HKEY_CURRENT_USER") {
		hkey = HKEY_CURRENT_USER;
	}
	else if (key == "HKEY_USERS") {
		hkey = HKEY_USERS;
	}
	else if (key == "HKEY_CURRENT_CONFIG") {
		hkey = HKEY_CURRENT_CONFIG;
	}
	return hkey;
}

// Regedit Read-Write : https://www.cnblogs.com/LyShark/p/15019685.html
// Regedit Read-Write : https://blog.csdn.net/xhlzjd/article/details/85250741
std::string Regedit::GetRegValue(const std::string& key, bool &is_dir)
{
	// Get HKey
	int pos_first = key.find_first_of("\\");
	const std::string hkey = key.substr(0, pos_first);

	// Take key remove hkey as lp_sub_key (Dir)
	const std::string lp_sub_key_dir = key.substr(pos_first + 1);
	const std::string val = Regedit::GetRegValue(hkey, lp_sub_key_dir, ""); 
	if (!val.empty()) {
		is_dir = true;
		return val;
	}

	is_dir = false;
	int pos_last = key.find_last_of("\\");
	const std::string lp_sub_key = key.substr(pos_first + 1, pos_last - pos_first - 1);
	const std::string reg_key = key.substr(pos_last + 1);
	return GetRegValue(hkey, lp_sub_key, reg_key); // reg_key is item in dir lp_sub_key
}

std::string Regedit::GetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key)
{
	HKEY hkey_root = GetRegHKeyRootHandle(hkey);
	HKEY hKey_return = NULL; // RegOpenKeyEx Return Value
	if (ERROR_SUCCESS != RegOpenKeyEx(hkey_root, reg_path.c_str(), 0, KEY_READ, &hKey_return)) {
        LOGE("RegOpenKeyEx failed. %s", reg_path.c_str());
		return "";
	}

	char key_value[256];
	DWORD keySz_type; // 接收键类型
	DWORD key_size;
	// 0 不定义值类型
	if (ERROR_SUCCESS != RegQueryValueEx(hKey_return, reg_key.c_str(), 0, &keySz_type, (LPBYTE)&key_value, &key_size)) {
		RegCloseKey(hkey_root);
		LOGE("RegQueryValueEx failed. %s", reg_path.c_str());
		return "";
	}

	LOGI("Regedit::GetRegValue() %s", key_value);
	RegCloseKey(hkey_root);
	return std::string(key_value, key_size);
}

bool Regedit::SetRegValue(const std::string& key, const std::string& value, const std::string& reg_type)
{
	bool is_dir = false;
	std::string old_val = GetRegValue(key, is_dir);
	if (old_val.size() > 0 && old_val[old_val.size() - 1] == '\0') {
		old_val = old_val.substr(0, old_val.size() - 1);
	}

	// Key Exist And value Same With Old
	if (value.size() == old_val.size() && value == old_val) {
		return true;
	}

	const std::string new_val = (old_val.size() > 0) ? old_val + ";" + value : value;
	std::string cmd = "";
	int pos_last = key.find_last_of("\\");
	std::string lp_key = key.substr(0, pos_last);
	if (is_dir || pos_last == key.size()-1) {
		cmd = "REG ADD \"" + lp_key + "\" /t " + reg_type + " /d \"" + new_val + "\" /f";
	}
	else {
		std::string reg_key = key.substr(pos_last + 1);
		cmd = "REG ADD \"" + lp_key + "\" /v \"" + reg_key + "\" /t " + reg_type + " /d \"" + new_val + "\" /f";
	}
    LOGI("cmd = %s", cmd.c_str());
	int ret = system(cmd.c_str());
	if (ret != 0) {
		//DWORD err = GetLastError();
		//LOGE("01: Error = %s", err);
		return false;
	}
	return true;
}

bool Regedit::DelRegValue(const std::string& key)
{
	if (key.empty()) {
		return false;
	}

	std::string cmd = "";
	int pos_last = key.find_last_of("\\");
	std::string lp_key = key.substr(0, pos_last);
	if (pos_last == key.size() - 1) { // Dir
		cmd = "echo yes | REG DELETE " + lp_key;
	}
	else {
		std::string reg_key = key.substr(pos_last + 1);
		cmd = "echo yes | REG DELETE " + lp_key + " /v " + reg_key;
	}
    LOGI("cmd = %s", cmd.c_str());
	int ret = system(cmd.c_str());
	if (ret != 0) {
		//DWORD err = GetLastError();
        //LOGE("01: Error = %s", err);
		return false;
	}
	return true;
}

#else // Not Win

std::string Regedit::GetRegValue(const std::string& key, bool &is_dir) {
	return ""; 
}

std::string Regedit::GetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key) { 
	return "";
}

bool Regedit::SetRegValue(const std::string& key, const std::string& value, const std::string& reg_type) {
	return false;
}

bool Regedit::DelRegValue(const std::string& key) {
	return false;
}

#endif // WIN

NS_CE_END
