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

#include <CLog/CKDefines.h>

#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>

#include <CLog/CLLog.h>
#include <CLog/CAppConf.h>
#include <CUtils/CUFile.h>

#include <QtEnvKit/DABuildScript.h>

#include "QDAMainWindow.h"

QString GetRootDir(const QString &bin_path) {
    QFileInfo info(bin_path);
    if (info.isFile()) {
        QDir bin_dir = info.absoluteDir();
        bin_dir.cdUp();
        return bin_dir.absolutePath();
    }

    return "";
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
        LOG_INFO << info << std::endl;
        QMessageBox::information(NULL, QStringLiteral("FixBuildScript"), QString::fromStdString(info));
        return 0;
    }

    std::string info = " Fix BuildScript " + script_path + " Failed: \n" + err_msg;
    LOG_INFO << info << std::endl;
    QMessageBox::critical(NULL, QStringLiteral("FixBuildScript"), QString::fromStdString(info));
    return 1;
}

int main(int argc, char *argv[])
{
    QString root_dir = GetRootDir(argv[0]);
    CKAppConf::GetInstance()->SetRootDir(root_dir.toStdString());
    
    for (size_t idx = 0; idx < argc; idx++) {
        LOG_INFO << argv[idx] << std::endl;
    }

    if (argc >= 2) {
        // Update run_win.bat / run_arm.sh / run_unix.sh
        return FixBuildScript(argv[1]);
    }

    return LoadApp(argc, argv);
}
