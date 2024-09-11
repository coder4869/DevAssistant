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

#include <CUtils/logger.h>
#include <CUtils/path_util.h>
#include <CUtils/CUFile.h>
#include <COSEnv/CERegedit.h>

#define LOG_TAG "TAG_COSEnv"

NS_CE_BEGIN

bool AppLoader::GetAppPath(const std::string &bin_path, std::string &output) {
    if (bin_path.empty()) {
        output = "";
        return false;
    }
#if defined(OSX)
    auto pos = bin_path.rfind(".app");
    output = bin_path.substr(0, pos + 4);
#elif defined(IOS)
    auto pos = bin_path.rfind(".ipa");
    output = bin_path.substr(0, pos + 4);
#else
    output = bin_path;
#endif
    return true;
}

bool AppLoader::GetAppDirPath(const std::string &bin_path, std::string &output) {
    if (bin_path.empty()) {
        output = "";
        return false;
    }
    auto bin_path_tmp = bin_path;
    std::string::size_type pos;
#ifdef WIN
    std::replace(bin_path_tmp.begin(), bin_path_tmp.end(), '\\', '/');
#elif defined(OSX)
    pos = bin_path_tmp.rfind(".app");
    bin_path_tmp = bin_path_tmp.substr(0, pos + 4);
#elif defined(IOS)
    pos = bin_path_tmp.rfind(".ipa");
    bin_path_tmp = bin_path_tmp.substr(0, pos + 4);
#endif
    pos = bin_path_tmp.find_last_of('/');
    output = bin_path.substr(0, pos);
    return true;
}

#if defined(APPLE) || defined(IOS) || defined(OSX) || defined(LINUX)
// RunCmdByPopen("pkgutil --packages", result)
static int RunCmdByPopen(const std::string &cmd_str, std::vector<std::string> &out_lines) {
    if (cmd_str.empty()) {
        LOGE("Command is empty.");
        return RET_ERROR;
    }
    FILE *fp = popen(cmd_str.c_str(), "r");
    if (fp == nullptr) {
        LOGE("Failed to execute command. %s ", cmd_str.c_str());
        return RET_ERROR;
    }
 
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        std::string line = buffer;
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        out_lines.emplace_back(line);
        LOGD("%s, cmd output line = %s", __FUNCTION__, line.c_str());
    }
 
    pclose(fp);
    return RET_OK;
}
#else
// TODO::adapt for WIN and Android
static int RunCmdByPopen(const std::string &cmd_str, std::vector<std::string> &out_lines) {
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
            LOGE("%s", message.c_str());
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
                LOGI("%s find %s, path = %s", __FUNCTION__, app_name.c_str(), output.c_str());
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
            LOGI("%s find %s, path = %s", __FUNCTION__, app_name.c_str(), output.c_str());
            return true;
        }
        
        // use only one result
        if (out_lines.size() == 1) {
            output = cmd_list[idx] + out_lines[0];
            LOGI("%s find %s, path = %s", __FUNCTION__, app_name.c_str(), output.c_str());
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
    LOGE("%s Error = %s", __FUNCTION__, output.c_str());
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

bool AppLoader::RunAsOSStart(const std::string& app_key, const std::string& bin_path)
{
#ifdef WIN
	std::string regkey = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\";
	auto tmp_path = bin_path;
	std::replace(tmp_path.begin(), tmp_path.end(), '/', '\\');
	//CE::Regedit::DelRegValue(regkey + app_key);
    return CE::Regedit::SetRegValue(regkey + app_key, tmp_path, "REG_SZ", true);

#elif defined(OSX)
    // TODO:: fix run as root issue
    return true;
    // plist 关键字：
    //    Label - 标识符，用来表示该任务的唯一性
    //    Program - 程序名称，用来说明运行哪个程序、脚本
    //    ProgramArguments - 数组程序名，同上，只是可以运行多个程序
    //    WatchPaths - 监控路径，当路径文件有变化是运行程序，也是数组
    //    RunAtLoad - 是否在加载的同时
    std::string start_plist = R"(
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
    <dict>
        <key>Label</key>
        <string>bundle—id</string>
        <key>ProgramArguments</key>
        <array>
            <string>bin-path</string>
        </array>
        <key>RunAtLoad</key>
        <true/>
    </dict>
</plist>
    )";
    
    // replace bundle_id
    std::string bundle_id = app_key;
    start_plist.replace(start_plist.find("bundle—id"), strlen("bundle—id"), bundle_id);
    
    // gen plist_path
    // https://zhuanlan.zhihu.com/p/25049770
    // https://www.cnblogs.com/gaocy/p/12567156.html
    //    /System/Library/LaunchDaemons/ （System-wide daemons provided by OS X）
    //    比如：apache 的 httpd 程序启动配置文件 org.apache.httpd.plist
    //    /System/Library/LaunchAgents/ （Mac OS X 为用户定义的任务项）
    //    /Library/LaunchDaemons （管理员定义的守护进程任务项）
    //    /Library/LaunchAgents （管理员为用户定义的任务项，开机启动项）
    //    ~/Library/LaunchAgents（用户自己定义的任务项，用户登录项）
    // 区别：
    //    /System/Library 目录下存放的是系统文件
    //    /Library 、~/Library/ 目录是用户存放的第三方软件
    //    LaunchDaemons 是用户未登陆前就启动的服务
    //    LaunchAgents 是用户登陆后启动的服务
    auto agents_path = utils::path::absolute_path("~/Library/LaunchAgents/");
    auto plist_path = agents_path.append("/" + bundle_id + ".plist");
    
    // replace app-path
    start_plist.replace(start_plist.find("bin-path"), strlen("bin-path"), bin_path);
    LOGI("start_plist = %s, bundle_id = %s, bin_path = %s", start_plist.c_str(), bundle_id.c_str(), bin_path.c_str());
    if (CU::File::SaveFileString(plist_path, start_plist) != 0) {
        LOGE("save to start plist error! plist = %s", plist_path.c_str());
        return false;
    }
    std::string load_cmd = "launchctl load " + plist_path;
    LOGI("start %s by cmd: %s", plist_path.c_str(), load_cmd.c_str());
    // For error: Try running `launchctl bootstrap` as root for richer errors.
    // Try: launchctl unload <plist_path>
    //      launchctl load <plist_path>
    return true;
#else   // Linux
    return false;
#endif
}

NS_CE_END
