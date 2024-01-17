// MIT License
//
// Copyright (c) 2021~2023 [coder4869](https://github.com/coder4869)
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

#include "CEAuthority.h"

#include <iostream>
#include <algorithm>

#ifdef WIN
#	include <windows.h>
#endif

#include <CLog/CLLog.h>
#include "CERegedit.h"

NS_CE_BEGIN

bool Authority::RunAsRoot(const std::string& bin_path) 
{
#ifdef WIN
	HINSTANCE hResult = ShellExecute(NULL, "runas", bin_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
	return true;
#else
	return false;
#endif // OSX
}

bool Authority::RunAsOSStart(const std::string& app_key, const std::string& app_path)
{
#ifdef WIN
	std::string regkey = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\";
	auto tmp_path = app_path;
	std::replace(tmp_path.begin(), tmp_path.end(), '/', '\\');
	//CE::Regedit::DelRegValue(regkey + app_key);
	auto ret2 = CE::Regedit::SetRegValue(regkey + app_key, tmp_path);

	return ret2;
#else
	return false;
#endif // OSX
}

NS_CE_END