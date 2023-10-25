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

// Right Action: https://www.cnblogs.com/pengsn/p/13563551.html
// Right Action: https://zhuanlan.zhihu.com/p/369716586
// https://blog.csdn.net/m0_43605481/article/details/121616732

#pragma once

#include <CLog/CKDefines.h>

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
