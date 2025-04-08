// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

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
#if WIN
    CU::String::LastNCharSubStr(app_path, '\\', 2, root_dir);
    CKAppConf::GetInstance()->SetRootDir(root_dir);
    CKAppConf::GetInstance()->SetRelativePath("app_icon", "data/Resource/AppIcon.ico");
#elif OSX
    CKAppConf::GetInstance()->SetRootDir(app_path + "/Contents");
#else // LINUX 
    CU::String::LastNCharSubStr(app_path, '/', 2, root_dir);
    CKAppConf::GetInstance()->SetRootDir(root_dir);
#endif
    LOGI("root_dir = %s, app_dir = %s, app_path = %s", root_dir.c_str(), app_dir.c_str(), app_path.c_str());
}

int SetInitStart(const char * bin_path) {
#if WIN
    std::string app_bin_abs = std::string(bin_path) + " %1";
    std::string app_icon_abs = CKAppConf::GetInstance()->GetRelativePath("app_icon");
    LOGI("app_bin_abs = %s", app_bin_abs.c_str());
    LOGI("app_icon_abs = %s", app_icon_abs.c_str());
    CE::RightAction::AddAction("DevAssist", app_bin_abs, "DevAssist", app_icon_abs,
                               CE::RightAction::Mode::FIX_SUFFIX, "batfile", true);
    //CE::RightAction::DelAction("DevAssist", CE::RightAction::Mode::FIX_SUFFIX, "batfile");
    
    // Auto Start
    return CE::AppLoader::RunAsOSStart("DevTools", bin_path);
    
//#elif defined(OSX)
//    std::string app_path;
//    CE::AppLoader::GetAppPath(bin_path, app_path);
//    return CE::AppLoader::RunAsOSStart("dev.coder4869.assistant", bin_path);
#else
    return 0;
#endif
}

}
