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

// https://blog.csdn.net/qq_45662588/article/details/117400914

#include "CEAppLoader.h"

#include <vector>
#include <iostream>
#include <algorithm>

#ifdef WIN
#	include <windows.h>
#endif

#include <CLog/CLLog.h>
#include "CERegedit.h"

NS_CE_BEGIN

#if (defined OSX) || (defined LINUX)
// RunCmdByPopen("pkgutil --packages", result)
static int RunCmdByPopen(const std::string &cmd_str, std::vector<std::string> &out_lines) {
    if (cmd_str.empty()) {
        std::cerr << "Command is empty." << std::endl;
        return RET_ERROR;
    }
    FILE *fp = popen(cmd_str.c_str(), "r");
    if (fp == nullptr) {
        std::cerr << "Failed to execute command." << std::endl;
        return RET_ERROR;
    }
 
//    std::string result;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        std::string line = buffer;
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        out_lines.emplace_back(line);
        std::cout << line << std::endl;
    }
 
    pclose(fp);
    return RET_OK;
}
#endif

// OSX  : /usr/local/bin > /usr/bin > /Applications > "pkgutil --packages"
// Linux: /usr/local/bin > /usr/bin
// Match priority: full equal > first same prefix > only one > other(failed)
bool AppLoader::GetAppInstallPath(const std::string &app_name, std::string &output)
{
#ifdef WIN
    return false;
#else // OSX or Linux
//#if _HAS_CXX17
    std::string message = "";
    std::string app_lower = app_name;
    std::transform(app_lower.begin(), app_lower.end(), app_lower.begin(), ::tolower);
    
    std::vector<std::string> cmd_list;
    cmd_list.emplace_back("/usr/local/bin/");
    cmd_list.emplace_back("/usr/bin/");
#ifdef OSX
    cmd_list.emplace_back("/Applications/");
#endif
    for (int idx = 0; idx<cmd_list.size(); idx++) {
        std::vector<std::string> out_lines;
        std::string cmd_str = "ls " + cmd_list[idx] + " | grep -i \"" + app_lower + "\"";
        int ret = RunCmdByPopen(cmd_str, out_lines);
        if (ret != RET_OK) {
            message = cmd_str + " popen failed !";
            LOG_ERR << message << std::endl;
            return false;
        }

        std::string pathes = "";
        std::string prefix_first = "";
        int line = 0;
        for (; line<out_lines.size(); line++) {
            std::string line_lower = out_lines[line];
            std::transform(line_lower.begin(), line_lower.end(), line_lower.begin(), ::tolower);
            
            // use full name equal first
            if (line_lower == app_lower) {
                output = cmd_list[idx] + out_lines[line];
                printf("%s find %s, path = %s \n", __FUNCTION__, app_name.c_str(), output.c_str());
                return true;
            }
            
            // record first with same prefix
            if (prefix_first == "" && line_lower.substr(0, app_lower.size()) == app_lower) {
                prefix_first = cmd_list[idx] + out_lines[line];
            }
            pathes += cmd_list[idx] + out_lines[line];
        }

        // use first same prefix name
        if (!prefix_first.empty()) {
            output = cmd_list[idx] + out_lines[0];
            printf("%s find %s, path = %s \n", __FUNCTION__, app_name.c_str(), output.c_str());
            return true;
        }
        
        // use only one result
        if (out_lines.size() == 1) {
            output = cmd_list[idx] + out_lines[0];
            printf("%s find %s, path = %s \n", __FUNCTION__, app_name.c_str(), output.c_str());
            return true;
        }
        
        if (out_lines.size() > 1) {
            // has multi query result, No full equal, no same prefix name
            message = "found " + pathes + " in dir " + cmd_list[idx] + "; ";
        } else {
            // empty query result
            message += "not found in dir " + cmd_list[idx] + "; ";
        }
    }
    output = app_name + " search result: " + message;
    printf("%s Error = %s \n", __FUNCTION__, output.c_str());
    return false;
#endif
}

bool AppLoader::RunAsRoot(const std::string& bin_path) 
{
#ifdef WIN
	HINSTANCE hResult = ShellExecute(NULL, "runas", bin_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
	return true;
#else   // OSX OR Linux
	return false;
#endif
}

bool AppLoader::RunAsOSStart(const std::string& app_key, const std::string& app_path)
{
#ifdef WIN
	std::string regkey = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\";
	auto tmp_path = app_path;
	std::replace(tmp_path.begin(), tmp_path.end(), '/', '\\');
	//CE::Regedit::DelRegValue(regkey + app_key);
	auto ret2 = CE::Regedit::SetRegValue(regkey + app_key, tmp_path);

	return ret2;
#else   // OSX OR Linux
    return false;
#endif
}

NS_CE_END
