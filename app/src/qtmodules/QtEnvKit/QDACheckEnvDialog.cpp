﻿// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDACheckEnvDialog.h"

#include <set>

#include <QDir>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include <CUtils/logger.h>
#include <CUtils/CUString.h>
#include <CApp/CAppConf.h>
#include <COSEnv/CESystemEnv.h>
#include <COSEnv/CERegedit.h>
#include <COSEnv/CEAppLoader.h>
#include <DevEnv/CodingTools.h>

#include <QtUIInfra/QtUIInfra.h>
#include <QtCoreKit/QtCoreKit.h>

#include "ui_QDACheckEnvDialog.h"

#define LOG_TAG "TAG_QtEnvKit"

QDACheckEnvDialog::QDACheckEnvDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDACheckEnvDialog)
{
    ui->setupUi(this);
    QUI::Style::SetTreeWidget(ui->envTreeWidget);

    ui->checkEnvBtn->setStyleSheet(QUI::Style::PushButton());
    connect(ui->checkEnvBtn, SIGNAL(clicked(bool)), this, SLOT(OnCheckEnv()));

    ui->tryFixBtn->setStyleSheet(QUI::Style::PushButton());
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
    
    auto infos = CodingTool::GetSoftInfos();
    int index = 0;
    for (auto &it : infos) {
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, QString::fromStdString(it.first));
        item->setText(1, QString::fromStdString(it.second.search_key));
        item->setText(2, QString::fromStdString(it.second.install_path));
        ui->envTreeWidget->insertTopLevelItem(index, item);
        index ++;
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
                    std::string app_path;
                    if (CE::AppLoader::GetAppInstallPath(soft_std, app_path)) {
                        path = QString::fromStdString(app_path);
                        key = "OS-Env";
                    } else {
                       path = soft + " in EnvVar " + key + " Not Found !";
                       //QMessageBox::warning(NULL, key, QString::fromStdString(pathes));
                    }
                }
            }
            else { // Get Info From Regedit
                bool is_dir = false;
                std::string value = CE::Regedit::GetRegValue(key_std, is_dir);
                path = QString::fromStdString(value);
                if (value.empty()) {
                    path = "Query Regedit Failed !";
                }
            }

            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, soft);
            item->setText(1, key);
            item->setText(2, path);
            ui->envTreeWidget->insertTopLevelItem(index, item);
            index++;
        }
    }
    
//    QMessageBox::information(NULL, QStringLiteral("OnCheckEnv"), "OnCheckEnv() Finish !");
}

void QDACheckEnvDialog::OnTryFixEnvValue()
{
    std::string script_env = CKAppConf::GetInstance()->GetRelativePath("script_env", "tools/env" + CMD_EXT.toStdString());
    QMessageBox::information(NULL, "script_env", QString::fromStdString(script_env));
    
    QByteArray output;
    bool ret = QCKCmd::ExecCmd(QString::fromStdString(script_env), QStringList(), output);
    if (!ret) {
        LOGE("script_env = %s \n output = %s", script_env.c_str(), output.data());
        QMessageBox::critical(NULL, QStringLiteral("OnTryFixEnvValue"), output.data());
        return;
    }

    QMessageBox::information(NULL, QStringLiteral("OnTryFixEnvValue"), "OnTryFixEnvValue() Finish !");
}
