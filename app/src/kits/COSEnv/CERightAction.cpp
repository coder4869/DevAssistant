// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "CERightAction.h"

#include <iostream>
#include <map>

#ifdef WIN
#	include <windows.h>
#endif

#include <CUtils/logger.h>
#include "CERegedit.h"

#define LOG_TAG "TAG_COSEnv"

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
		LOGE("Empty Parameter Exist! key = %s, action = %s, tips = %s, mode = %d, suffix = %s",
             key.c_str(), action.c_str(), tips.c_str(), (int)mode, suffix.c_str());
		return 1;
	}

#ifdef WIN
	std::string reg_path = GetRegPrefix(mode);
	if (reg_path.empty()) {
		LOGE("Invalid Mode ! mode = %d", (int)mode);
		return 2;
	}

	std::string reg_val = action;
	if (mode == CE::RightAction::Mode::FIX_SUFFIX) {
		reg_path.append(suffix + "\\shell\\" + key + "\\");
	} else {
		reg_path.append(key + "\\");
	}

    LOGE("reg_path = %s, reg_icon = %s, reg_command = %s",
         reg_path.c_str(), icon_path.c_str(), reg_val.c_str());

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
        LOGE("Empty Parameter Exist! key = %s, mode = %d, suffix = %s", key.c_str(), (int)mode, suffix.c_str());
		return 1;
	}

#ifdef WIN
	std::string reg_path = GetRegPrefix(mode);
	if (reg_path.empty()) {
        LOGE("Invalid Mode ! mode = %d", (int)mode);
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
