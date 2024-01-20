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

#include <stdio.h>

#include <algorithm>

#include <CLog/CLLog.h>
#include <CLog/CAppConf.h>
#include <COSEnv/CEAppLoader.h>
#include <COSEnv/CERightAction.h>
#include <COSEnv/CETrayIcon.h>

std::string GetRootDir(const std::string &bin_path) {
    if (bin_path.empty()) {
        return "";
    }

    auto bin_path_tmp = bin_path;
#ifdef WIN
    std::replace(bin_path_tmp.begin(), bin_path_tmp.end(), '\\', '/');
#endif // WIN
    auto pos_l = bin_path_tmp.find_last_not_of('/');
    if (pos_l < bin_path_tmp.length() - 1) {
        bin_path_tmp = bin_path_tmp.substr(0, pos_l + 1);
    }

    auto pos_e = bin_path_tmp.find_last_of('/');
    bin_path_tmp = bin_path_tmp.substr(0, pos_e);

    pos_e = bin_path_tmp.find_last_of('/');
    bin_path_tmp = bin_path_tmp.substr(0, pos_e);

    return bin_path_tmp;
}

std::string GetBinRelativePath(const std::string& bin_path) {
    if (bin_path.empty()) {
        return "";
    }

    auto bin_path_tmp = bin_path;
#ifdef WIN
    std::replace(bin_path_tmp.begin(), bin_path_tmp.end(), '\\', '/');
#endif // WIN
    auto pos_l = bin_path_tmp.find_last_not_of('/');
    if (pos_l < bin_path_tmp.length() - 1) {
        bin_path_tmp = bin_path_tmp.substr(0, pos_l + 1);
    }

    auto pos_e = bin_path_tmp.find_last_of('/');
    bin_path_tmp = bin_path_tmp.substr(0, pos_e);
    pos_e = bin_path_tmp.find_last_of('/');
    
    return  bin_path_tmp.substr(pos_e+1);
}

int main(int argc, char *argv[])
{
    auto root_dir = GetRootDir(argv[0]);
    auto app_bin = GetBinRelativePath(argv[0]);
    LOG_INFO << " app_bin = " << app_bin << std::endl;

    CKAppConf::GetInstance()->SetRootDir(root_dir);
    CKAppConf::GetInstance()->SetRelativePath("app_bin", app_bin + "/DevAssistant.exe");
    CKAppConf::GetInstance()->SetRelativePath("app_icon", "data/Resource/AppIcon.ico");

    std::string app_bin_abs = CKAppConf::GetInstance()->GetRelativePath("app_bin") + " %1";
    std::string app_icon_abs = CKAppConf::GetInstance()->GetRelativePath("app_icon");
    LOG_INFO << " app_bin_abs = " << app_bin_abs << std::endl;
    LOG_INFO << " app_icon_abs = " << app_icon_abs << std::endl;
    CE::RightAction::AddAction("DevAssist", app_bin_abs, "DevAssist", app_icon_abs,
                                CE::RightAction::Mode::FIX_SUFFIX, "batfile", true);
    //CE::RightAction::AddAction("DevAssist", "D:/Research/DevAssistant/app/bin64/Release/DevAssistant.exe", 
    //                            "DevAssist", "D:/Research/DevAssistant/app/scripts/cmake/cmake-win/res/AppIcon.ico",
    //                            CE::RightAction::Mode::FIX_SUFFIX, "batfile");
    //CE::RightAction::DelAction("DevAssist", CE::RightAction::Mode::FIX_SUFFIX, "batfile");

    // Auto Start
    auto ret2 = CE::AppLoader::RunAsOSStart("DevTools", root_dir + "/bin64/DevAssistant.exe");

    return 0;
}
