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

#include <CCoreKit/CCoreKit.h>
#include <CCoreKit/os/CKSystemEnv.h>
#include <CCoreKit/os/CKRegisterTable.h>

#include <QtUIInfra/QtUIInfra.h>
#include <QtCoreKit/QtCoreKit.h>

#include "ui_QDACheckEnvDialog.h"

QDACheckEnvDialog::QDACheckEnvDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDACheckEnvDialog)
{
    ui->setupUi(this);
    QUIStyle::SetTreeWidget(ui->envTreeWidget);

    QUIStyle::SetPushButton(ui->checkEnvBtn);
    connect(ui->checkEnvBtn, SIGNAL(clicked(bool)), this, SLOT(OnCheckEnv()));

    QUIStyle::SetPushButton(ui->tryFixBtn);
    connect(ui->tryFixBtn, SIGNAL(clicked(bool)), this, SLOT(OnTryFixEnvValue()));
}

QDACheckEnvDialog::~QDACheckEnvDialog()
{
    delete ui;
}

void QDACheckEnvDialog::OnCheckEnv()
{
    emit SigShowWidget(this);
    ui->envTreeWidget->clear();

    std::string json_file = CKAppConf::GetInstance()->GetRelativePath("env_config", "conf/env_config.json");
    QJsonArray json_arr;
    if (!QCKJson::LoadJsonArrayFromFile(QString::fromStdString(json_file), json_arr)) {
        return;
    }
    
    // Item
    //{
    //    "System" : "Windows,Darwin,Linux",
    //    "From" : "EnvVar", EnvVar or REG
    //    "Key" : "PATH",
    //    "Soft" : "CMake"
    //}
    // REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\devenv.exe" >> tmp.log
    for (size_t idx = 0; idx < json_arr.size(); idx++) {
        QJsonObject obj = json_arr.at(idx).toObject();

        // 判断 OS

        // 判断获取方式
        if (obj.contains("From") && obj.contains("Key") && obj.contains("Soft"))
        {
            QString key = obj["Key"].toString();
            std::string key_std = key.toStdString();
            QString soft = obj["Soft"].toString();
            std::string soft_std = soft.toStdString();

            QString path = "";
            if (obj["From"] == "EnvVar") { // Get Info From Environment Var
                bool has_key = false;
                std::string pathes = "";

                auto path_set = CK::SystemEnv::SplitEnvValue(key_std.c_str());
                for (auto iter = path_set.begin(); iter != path_set.end(); iter++) {
                    std::string tmp = *iter;
                    if (tmp.find(soft_std) != std::string::npos) {
                        has_key = true;
                        path = QString::fromStdString(tmp);
                        break;
                    }

                    pathes = pathes + "\n" + iter->c_str();
                }

                if (!has_key) {
                    path = soft + " in EnvVar " + key + " Not Found !";
                    //QMessageBox::warning(NULL, key, QString::fromStdString(pathes));
                }
            }
            else { // Get Info From Register Table
                bool is_dir = false;
                std::string value = CK::RegisterTable::GetRegValue(key_std, is_dir);
                path = QString::fromStdString(value);
                if (value.empty()) {
                    path = "Query Register Table Failed !";
                }
            }

            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, soft);
            item->setText(1, key);
            item->setText(2, path);
            ui->envTreeWidget->insertTopLevelItem(0, item);
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
    QMessageBox::information(NULL, QStringLiteral("OnCheckEnv"), "OnCheckEnv() Finish !");
}

void QDACheckEnvDialog::OnTryFixEnvValue()
{
    qDebug() << __FUNCTION__ << endl;

    std::string run_script = CKAppConf::GetInstance()->GetRelativePath("run_script", "Resources/run_win.bat");
    QStringList dataLines;
    if (QCKFile::State::Succeed != QCKFile::LoadFileLines(QString::fromStdString(run_script), dataLines)) {
        qDebug() << __FUNCTION__ << " LoadFileLines Failed !" << endl;
        return;
    }
    
    if (dataLines.size() == 0) {
        qDebug() << __FUNCTION__ << " Empty " << QString::fromStdString(run_script) << endl;
    }

    for (size_t idx = 0; idx < dataLines.size(); idx++) {
        qDebug() << __FUNCTION__ << dataLines[idx] << endl;
    }

    QMessageBox::information(NULL, QStringLiteral("OnTryFixEnvValue"), "OnTryFixEnvValue() Finish !");
}
