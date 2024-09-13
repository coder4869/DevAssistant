// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>

#include <CUtils/logger.h>
#include <CUtils/CUFile.h>
#include <CApp/CAppConf.h>
#include <COSEnv/CEAppLoader.h>

#include <QtEnvKit/DABuildScript.h>

#include "AppLoader.h"
#include "QDAMainWindow.h"

#define LOG_TAG "TAG_DevAssistant"

QString GetRootDir(const QString &bin_path) {
    QFileInfo info(bin_path);
    if (info.isFile()) {
        QDir bin_dir = info.absoluteDir();
        bin_dir.cdUp();
        return bin_dir.absolutePath();
    }

    return "";
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

    return  bin_path_tmp.substr(pos_e + 1);
}

int LoadApp(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("DevAssistant");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QDAMainWindow window;
    window.setWindowTitle("DevAssistant");
    window.showMaximized();
    window.LoadWelcome();

    return app.exec();
}

int FixBuildScript(const std::string& script_path) {
    std::string err_msg = "";
    bool ret = QEK::BuildScript::Update(script_path, err_msg);

    if (ret) {
        CU::File::SaveFileString(script_path, err_msg);
        std::string info = " Fix BuildScript " + script_path + " Succeed: \n" + err_msg;
        LOGI("info = %s", info.c_str());
        QMessageBox::information(NULL, QStringLiteral("FixBuildScript"), QString::fromStdString(info));
        return 0;
    }

    std::string info = " Fix BuildScript " + script_path + " Failed: \n" + err_msg;
    LOGI("info = %s", info.c_str());
    QMessageBox::critical(NULL, QStringLiteral("FixBuildScript"), QString::fromStdString(info));
    return 1;
}

int main(int argc, char *argv[])
{
    QString root_dir = GetRootDir(argv[0]);
    Logger::SetLogWriter(root_dir.toStdString() + "/logs");
    
    App::InitAppConfig(argv[0]);
    App::SetInitStart(argv[0]);

    for (size_t idx = 0; idx < argc; idx++) {
        LOGI("argv[%d] = %s", (int)idx, argv[idx]);
    }

    if (argc >= 2) {
        // Update run_win.bat / run_arm.sh / run_unix.sh
        return FixBuildScript(argv[1]);
    }

//#ifdef WIN
//    // Run InstallReg.exe as Root Authority
//    auto app_bin = GetBinRelativePath(argv[0]);
//    auto root_flag = CKAppConf::GetInstance()->GetRelativePath("app_bin", app_bin + "/root_flag");
//    if (CU::File::IsFileExist(root_flag) != 0) {
//        auto bin_install = CKAppConf::GetInstance()->GetRelativePath("app_bin", app_bin + "/InstallReg.exe");
//        if (CE::AppLoader::RunAsRoot(bin_install)) {
//            CU::File::SaveFileString(root_flag, "AutoStart");
//        }
//    }
//#endif

    return LoadApp(argc, argv);
}
