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

#include "CKRegisterTable.h"

#include <iostream>

#ifdef WIN
#	include <windows.h>
#endif

#include <CCoreKit/log/CKLog.h>

namespace CK {
#ifdef WIN
HKEY GetRegHKeyRootHandle(const std::string &key) 
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

// Register Table Read-Write : https://www.cnblogs.com/LyShark/p/15019685.html
// Register Table Read-Write : https://blog.csdn.net/xhlzjd/article/details/85250741
std::string RegisterTable::GetRegValue(const std::string& key)
{
	int pos_first = key.find_first_of("\\");
	int pos_last = key.find_last_of("\\");

	const std::string hkey = key.substr(0, pos_first);
	const std::string lp_sub_key = key.substr(pos_first + 1, pos_last - pos_first);
	const std::string reg_key = key.substr(pos_last + 1);

	const std::string val = RegisterTable::GetRegValue(hkey, key.substr(pos_first + 1), ""); // Take key remove hkey as lp_sub_key
	if (!val.empty()) {
		return val;
	}
	return GetRegValue(hkey, lp_sub_key, reg_key);
}

std::string RegisterTable::GetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key)
{
	HKEY hkey_root_handle = GetRegHKeyRootHandle(hkey);
	HKEY hKey_return = NULL; // RegOpenKeyEx Return Value
	if (ERROR_SUCCESS != RegOpenKeyEx(hkey_root_handle, reg_path.c_str(), 0, KEY_READ, &hKey_return)) {
		LOG_ERR << "RegOpenKeyEx failed." << std::endl;
		return "";
	}

	char key_value[256];
	DWORD keySz_type; // 接收键类型
	DWORD key_size;
	// 0 不定义值类型
	if (ERROR_SUCCESS != RegQueryValueEx(hKey_return, reg_key.c_str(), 0, &keySz_type, (LPBYTE)&key_value, &key_size)) {
		RegCloseKey(hkey_root_handle);
		LOG_ERR << "RegQueryValueEx failed." << std::endl;
		return "";
	}

	LOG_INFO << key_value << std::endl;
	RegCloseKey(hkey_root_handle);
	return std::string(key_value, key_size);
}

bool RegisterTable::SetRegValue(const std::string& key, const std::string& value)
{
	int pos_first = key.find_first_of("\\");
	int pos_last = key.find_last_of("\\");

	std::string hkey = key.substr(0, pos_first);
	std::string lp_sub_key = key.substr(pos_first + 1, pos_last - pos_first);
	std::string reg_key = key.substr(pos_last + 1);

	bool ret = SetRegValue(hkey, key.substr(pos_first + 1), "", value); // Take key remove hkey as lp_sub_key
	return ret || SetRegValue(hkey, lp_sub_key, reg_key, value);
}

bool RegisterTable::SetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key,
	const std::string& reg_value)
{	
	// Check key Exist Or Not
	if (reg_value == GetRegValue(hkey, reg_path, reg_key)) {
		return true;
	}

	HKEY hkey_root_handle = GetRegHKeyRootHandle(hkey);
	HKEY hKey_return = NULL; // RegOpenKeyEx Return Value
	if (ERROR_SUCCESS == RegOpenKeyEx(hkey_root_handle, reg_path.c_str(), 0, KEY_WRITE, &hKey_return)) {
		//RegSetValueEx(hKey_return, )
		LOG_ERR << "RegOpenKeyEx failed." << std::endl;
		return false;
	}

	//char key_value[256];
	//DWORD keySz_type; // 接收键类型
	//DWORD key_size;
	//// 0 不定义值类型
	//if (ERROR_SUCCESS != RegReplaceKey(hKey_return, reg_key.c_str(), 0, &keySz_type, (LPBYTE)&key_value, &key_size)) {
	//	RegCloseKey(hkey_root_handle);

	//	LOG_ERR << "RegQueryValueEx failed." << std::endl;
	//	return false;
	//}

	//LOG_INFO << key_value << std::endl;
	RegCloseKey(hkey_root_handle);

	return true;
}


#else // Not Win

std::string RegisterTable::GetRegValue(const std::string& key) {
	return ""; 
}

std::string RegisterTable::GetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key) { 
	return "";
}

bool RegisterTable::SetRegValue(const std::string& key, const std::string& value) {
	return false;
}

bool RegisterTable::SetRegValue(const std::string& hkey, const std::string& reg_path, const std::string& reg_key = "",
	const std::string& reg_value) {
	return false;
}

#endif // WIN

} //namespace CK
