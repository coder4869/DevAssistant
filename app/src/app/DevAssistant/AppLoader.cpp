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

#include <algorithm>

#include <CUtils/logger.h>
#include <CUtils/CUString.h>
#include <CApp/CAppConf.h>
#include <COSEnv/CEAppLoader.h>
#include <COSEnv/CERightAction.h>
#include <COSEnv/CETrayIcon.h>

#include "AppLoader.h"

#define LOG_TAG "TAG_DevAssistant"

namespace App {

void InitAppConfig(const char *bin_path) {
    std::string app_path, app_dir, root_dir;
    CE::AppLoader::GetAppPath(bin_path, app_path);
    CE::AppLoader::GetAppDirPath(bin_path, app_dir);
#ifdef OSX
    CKAppConf::GetInstance()->SetRootDir(app_path + "/Contents");
#else
    CU::String::LastNCharSubStr(app_dir, '/', 2, root_dir);
    CKAppConf::GetInstance()->SetRootDir(root_dir);
    CKAppConf::GetInstance()->SetRelativePath("app_icon", "data/Resource/AppIcon.ico");
#endif
    LOGI("root_dir = %s, app_dir = %s, app_path = %s", root_dir.c_str(), app_dir.c_str(), app_path.c_str());
}

int SetInitStart(const char * bin_path) {
#ifdef WIN
    std::string app_bin_abs = std::string(bin_path) + " %1";
    std::string app_icon_abs = CKAppConf::GetInstance()->GetRelativePath("app_icon");
    LOGI("app_bin_abs = %s", app_bin_abs.c_str());
    LOGI("app_icon_abs = %s", app_icon_abs.c_str());
    CE::RightAction::AddAction("DevAssist", app_bin_abs, "DevAssist", app_icon_abs,
                               CE::RightAction::Mode::FIX_SUFFIX, "batfile", true);
    //CE::RightAction::DelAction("DevAssist", CE::RightAction::Mode::FIX_SUFFIX, "batfile");
    
    // Auto Start
    return CE::AppLoader::RunAsOSStart("DevTools", bin_path);
    
#elif defined(OSX)
    return CE::AppLoader::RunAsOSStart("dev.coder4869.assistant", bin_path);
#else
    return 0;
#endif
}

}
