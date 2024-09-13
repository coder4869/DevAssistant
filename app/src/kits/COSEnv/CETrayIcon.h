// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

// Right Action: https://www.cnblogs.com/pengsn/p/13563551.html
// Right Action: https://zhuanlan.zhihu.com/p/369716586
// https://blog.csdn.net/m0_43605481/article/details/121616732

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <string>

#include "COSEnvDef.h"

#define WM_TO_TRAY (WM_USER + 5)

NS_CE_BEGIN

namespace TrayIcon {
	/// @param icon_name Icon ID. e.g. Windows Icon in app .rc (IDI_ICON1)
	/// @param mode windows : 0-NIM_ADD, 1-NIM_MODIFY, 2-NIM_DELETE, 3-NIM_SETFOCUS, 4-NIM_SETVERSION
	void SetIcon(int winid, const std::string& icon_name, const std::string& tips, unsigned long mode = 0);

	/// @brief show window from TrayIcon
	/// @param winid window id to show
	void ShowWindow(int winid, bool show = true);

	/// @param winid id of target window for removing TrayIcon.
	void DelIcon(int winid);
}

NS_CE_END
