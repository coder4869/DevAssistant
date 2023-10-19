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

#include <set>

#include <QDir>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include <CLog/CLLog.h>
#include <CLog/CAppConf.h>
#include <CUtils/CUString.h>
#include <COSEnv/CESystemEnv.h>
#include <COSEnv/CERegisterTable.h>

#include <QtUIInfra/QtUIInfra.h>
#include <QtCoreKit/QtCoreKit.h>

#include "ui_QDACheckEnvDialog.h"

QDACheckEnvDialog::QDACheckEnvDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDACheckEnvDialog)
{
    ui->setupUi(this);
    QUI::Style::SetTreeWidget(ui->envTreeWidget);

    QUI::Style::SetPushButton(ui->checkEnvBtn);
    connect(ui->checkEnvBtn, SIGNAL(clicked(bool)), this, SLOT(OnCheckEnv()));

    QUI::Style::SetPushButton(ui->tryFixBtn);
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
        bool support = true;
        if (obj.contains("System")) {
            QString key = obj["System"].toString();
            std::set<std::string> values;
            CU::String::SplitStringToSet(key.toStdString(), ",", values);
            bool has_os = false;
            for (auto val : values) {
                if (val == CE::OS_NAME) {
                    has_os = true;
                }
            }
            support = has_os;
        }
        if (!support) {
            continue;
        }
        
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

                auto path_set = CE::SystemEnv::SplitEnvValue(key_std.c_str());
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
                std::string value = CE::RegisterTable::GetRegValue(key_std, is_dir);
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

    QMessageBox::information(NULL, QStringLiteral("OnCheckEnv"), "OnCheckEnv() Finish !");
}

void QDACheckEnvDialog::OnTryFixEnvValue()
{
    LOG_INFO << __FUNCTION__ << std::endl;

    std::string script_env = CKAppConf::GetInstance()->GetRelativePath("script_env", "tools/env" + CMD_EXT.toStdString());
    QMessageBox::information(NULL, "script_env", QString::fromStdString(script_env));
    
    QByteArray output;
    bool ret = QCKCmd::ExecCmd(QString::fromStdString(script_env), QStringList(), output);
    if (!ret) {
        LOG_ERR << script_env << "\n" << output.data() << std::endl;
        QMessageBox::critical(NULL, QStringLiteral("OnTryFixEnvValue"), output.data());
        return;
    }

    QMessageBox::information(NULL, QStringLiteral("OnTryFixEnvValue"), "OnTryFixEnvValue() Finish !");
}
