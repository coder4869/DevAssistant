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

#include "CERightAction.h"

#include <iostream>
#include <map>

#ifdef WIN
#	include <windows.h>
#endif

#include <CUtils/log.h>
#include "CERegedit.h"

NS_CE_BEGIN


static std::string GetRegPrefix(RightAction::Mode mode) 
{
	static std::map<RightAction::Mode, std::string> mode_prefix_map;
	mode_prefix_map[RightAction::Mode::ALL_FILES] = "HKEY_CLASSES_ROOT\\*\\shell\\";
	mode_prefix_map[RightAction::Mode::FIX_SUFFIX] = "HKEY_CLASSES_ROOT\\";	
	mode_prefix_map[RightAction::Mode::FOLDER] = "HKEY_CLASSES_ROOT\\Folder\\shell\\";
	mode_prefix_map[RightAction::Mode::DIR] = "HKEY_CLASSES_ROOT\\Directory\\shell\\";
	mode_prefix_map[RightAction::Mode::DIR_BACK] = "HKEY_CLASSES_ROOT\\Directory\\Background\\shell\\";

	auto iter = mode_prefix_map.find(mode);
	if (iter == mode_prefix_map.end()) {
		return "";
	}
	return iter->second;
}

int RightAction::AddAction(const std::string& key, const std::string& action, 
							const std::string& tips, const std::string& icon_path,
							RightAction::Mode mode, const std::string& suffix,
							bool clear_old)
{
	if (key.empty() || action.empty() || tips.empty() 
		|| (mode == RightAction::Mode::FIX_SUFFIX && suffix.empty())) {
		LOG_ERR << " Empty Parameter Exist! key = " << key 
				<< " action = " << action << " tips = " << tips
				<< " mode = " << (int)mode << " suffix = " << suffix << std::endl;
		return 1;
	}

#ifdef WIN
	std::string reg_path = GetRegPrefix(mode);
	if (reg_path.empty()) {
		LOG_ERR << " Invalid Mode ! mode = " << (int)mode << std::endl;
		return 2;
	}

	std::string reg_val = action;
	if (mode == CE::RightAction::Mode::FIX_SUFFIX) {
		reg_path.append(suffix + "\\shell\\" + key + "\\");
	} else {
		reg_path.append(key + "\\");
	}

	LOG_ERR << " reg_path = " << reg_path 
							<< " reg_icon = " << icon_path
							<< " reg_command = " << reg_val << std::endl;
	if (clear_old) {
		DelAction(key, mode, suffix);
	}

	auto ret1 = CE::Regedit::SetRegValue(reg_path, tips);
	auto ret2 = CE::Regedit::SetRegValue(reg_path + "Icon", icon_path);
	auto ret3 = CE::Regedit::SetRegValue(reg_path + "command\\", reg_val, "REG_EXPAND_SZ");

	return ret1 && ret2 && ret3 ? 0 : 3;
#else
	return 0;
#endif // WIN
}

int RightAction::DelAction(const std::string& key, RightAction::Mode mode, const std::string& suffix)
{
	if (key.empty() || (mode == RightAction::Mode::FIX_SUFFIX && suffix.empty())) {
		LOG_ERR << " Empty Parameter Exist! key = " << key 
				<< " mode = " << (int)mode << " suffix = " << suffix << std::endl;
		return 1;
	}

#ifdef WIN
	std::string reg_path = GetRegPrefix(mode);
	if (reg_path.empty()) {
		LOG_ERR << " Invalid Mode ! mode = " << (int)mode << std::endl;
		return 2;
}

	if (mode == CE::RightAction::Mode::FIX_SUFFIX) {
		reg_path.append(suffix + "\\shell\\" + key + "\\");
	} else {
		reg_path.append(key + "\\");
	}

	auto ret = CE::Regedit::DelRegValue(reg_path);
	return ret ? 0 : 3;
#else
	return 0;
#endif // WIN
}

NS_CE_END
