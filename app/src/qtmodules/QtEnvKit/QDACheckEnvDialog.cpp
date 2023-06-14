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

#include "QDACheckEnvDialog.h"

#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include <QtUIInfra/QtUIInfra.h>
#include <QtCoreKit/QtCoreKit.h>
#include <CCoreKit/CCoreKit.h>

#include "ui_QDACheckEnvDialog.h"

QDACheckEnvDialog::QDACheckEnvDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDACheckEnvDialog)
{
    ui->setupUi(this);
    QUIStyle::SetTreeWidget(ui->envTreeWidget);
    QUIStyle::SetPushButton(ui->checkEnvBtn);
    QUIStyle::SetPushButton(ui->tryFixBtn);
}

QDACheckEnvDialog::~QDACheckEnvDialog()
{
    delete ui;
}


void QDACheckEnvDialog::OnCheckEnv()
{
    emit SigShowWidget(this);
    ui->envTreeWidget->clear();

    QString json_file = "";
    QJsonArray json_arr;
    if (!QCKJson::LoadJsonArrayFromFile(json_file, json_arr)) {
        return;
    }
    
    //{
    //    "System" : "Windows,Darwin,Linux",
    //    "From" : "EnvVar", EnvVar or REG
    //    "Key" : "PATH",
    //    "Soft" : "CMake"
    //}
    // REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\devenv.exe" >> tmp.log
    QStringList keys;
    keys << "Visual Studio" << "Python" << "CMake" << "Qt" ;

    for (size_t idx = 0; idx < keys.size(); idx++)
    {
        std::string key_std = keys[idx].toStdString();
        bool has_key = false;
        std::string pathes = "";

        auto path_set = CKSystemEnv::SplitEnvValue("PATH");
        for (auto iter = path_set.begin(); iter != path_set.end(); iter++) {
            std::string tmp = *iter;
            if (tmp.find(key_std) != std::string::npos) {
                QTreeWidgetItem* item = new QTreeWidgetItem;
                item->setText(0, keys[idx]);
                item->setText(1, "PATH");
                item->setText(2, QString::fromStdString(tmp));
                ui->envTreeWidget->insertTopLevelItem(0, item);
                has_key = true;
                break;
            }

            pathes = pathes + "\n" + iter->c_str();
        }
        
        if (!has_key) {
            QMessageBox::information(NULL, __FUNCTION__, pathes.c_str());
        }
    }

   

    //QString dirPath = QCoreApplication::applicationDirPath();
    //qDebug() << "App Dir Path = " << dirPath << endl;
    //QString pycmd = QCKCmd::GetPyBin() + dirPath + "/../Resources/plugins/env/run.py --config env.json";
    //QMessageBox::information(NULL, "pycmd", pycmd);
    //
    //QByteArray output;
    //bool ret = QCKCmd::ExecCmd(pycmd, QStringList(), output);
    //if (!ret) {
    //    qDebug() << pycmd << "\n" << output.data() << endl;
    //    QMessageBox::critical(NULL, QStringLiteral("OnCheckEnv"), output.data());
    //    return;
    //}
    //QMessageBox::information(NULL, QStringLiteral("OnCheckEnv"), "Succeed!");
}
