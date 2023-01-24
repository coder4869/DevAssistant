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

#include "QDAProjectDetailDialog.h"

#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include <QtCoreKit/QtCoreKit.h>
#include <QtScriptsKit/QtScriptsKit.h>

#include "ui_QDAProjectDetailDialog.h"

QDAProjectDetailDialog::QDAProjectDetailDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAProjectDetailDialog)
{
//    QSKPython::InitPy();
    
    ui->setupUi(this);
    
    connect(ui->createProjectBtn, SIGNAL(clicked(bool)), this, SLOT(OnCreate()));
    connect(ui->loadProjectConfigBtn, SIGNAL(clicked(bool)), this, SLOT(OnLoadConfig()));
    connect(ui->saveProjectConfigBtn, SIGNAL(clicked(bool)), this, SLOT(OnSaveConfig()));    
}

QDAProjectDetailDialog::~QDAProjectDetailDialog()
{
    delete ui;
}

void QDAProjectDetailDialog::OnProjectCreate()
{
    emit SigShowWidget(this);
    ui->createProjectBtn->show();
    ui->loadProjectConfigBtn->hide();
    ui->saveProjectConfigBtn->hide();
    ui->viewProjectConfigText->setPlainText("Project Config Json");
    show_mode = ShowMode::Add;

    QStringList list = QCKFile::SelectFiles(STRING("Files(*.json)"), false);
    if (list.size() == 1) {
        QDAProjectConfig::config_json_type = QDAProjectConfig::JsonType::Create;
        QString json_str = QDAProjectConfig::LoadJsonConfig(list[0]);
        ui->viewProjectConfigText->setPlainText(json_str);
        // parse json_str to config && AddConfig(); && save change in OnCreate();
    }
}

void QDAProjectDetailDialog::OnProjectOpen()
{
    emit SigShowWidget(this);
    ui->createProjectBtn->hide();
    ui->loadProjectConfigBtn->show();
    ui->saveProjectConfigBtn->show();
    ui->viewProjectConfigText->setPlainText("Project Config Json");
    show_mode = ShowMode::Open;

    QStringList list = QCKFile::SelectDirectory(false);
    if (list.size() == 1) {
        QDAProjectConfig::config_json_type = QDAProjectConfig::JsonType::Open;
        QString json_file = list[0] + PROJECT_CONF_JSON;
        QString json_str = QDAProjectConfig::LoadJsonConfig(json_file);
        ui->viewProjectConfigText->setPlainText(json_str);
        
        // parse json_str to config && AddConfig(); && save change
        is_view_avaliable = UpdateJsonAndConfig(true); // check proj_dir && save json
    }
}

void QDAProjectDetailDialog::OnProjectView()
{
    emit SigShowWidget(this);
    ui->createProjectBtn->hide();
    ui->loadProjectConfigBtn->show();
    ui->saveProjectConfigBtn->show();
    ui->viewProjectConfigText->setPlainText("Project Config Json");
    show_mode = ShowMode::View;

    if (is_view_avaliable) {
        QDAProjectConfig::config_json_type = QDAProjectConfig::JsonType::Open;
        QDAProjectConfig::ConfigInfo config = QDAProjectConfig::GetConfig();
        QString json_str = QDAProjectConfig::JsonStringFromConfig(config);
        ui->viewProjectConfigText->setPlainText(json_str);
    } else {
        QMessageBox::critical(NULL, QStringLiteral("Project"), "Ensure Create or Open Project succeed !");
    }
}

void QDAProjectDetailDialog::OnCreate()
{
    if (!UpdateJsonAndConfig(false)) { // no check proj_dir && save json for create
        QMessageBox::critical(NULL, QStringLiteral("Project"), QStringLiteral("OnSaveConfig(); failed !"));
        return;
    }
    
    QDAProjectConfig::ConfigInfo config = QDAProjectConfig::GetConfig();
    if (config.json_file.isEmpty()) {
        QMessageBox::critical(NULL, QStringLiteral("Project"), QStringLiteral("Empty json config file!"));
        return;
    }
    
    QString dirPath = QCoreApplication::applicationDirPath();
    qDebug() << "App Dir Path = " << dirPath << endl;
    QString pycmd = PY_BIN + dirPath + "/../Resources/plugins/project/run.py --type project --config " + config.json_file;

    QStringList options;
    QByteArray output;
    QMessageBox::information(NULL, "pycmd", pycmd);
    bool ret = QCKCmd::ExecCmd(pycmd, options, output);
    if (!ret) {
        qDebug() << pycmd << "\n" << output.data() << endl;
        QMessageBox::critical(NULL, QStringLiteral("Project Create"), output.data());
        return;
    }
    QMessageBox::information(NULL, QStringLiteral("Project Create"), "Succeed!");
}

bool QDAProjectDetailDialog::OnLoadConfig()
{
    // ReLoad Current Project's JSON Config
    QDAProjectConfig::ConfigInfo config = QDAProjectConfig::GetConfig();
    QString json_str = QDAProjectConfig::LoadJsonConfig(config.json_file);
    ui->viewProjectConfigText->setPlainText(json_str);
    
    // parse json_str to config and AddConfig();
    return QDAProjectConfig::AddConfigByString(json_str);
}

bool QDAProjectDetailDialog::OnSaveConfig()
{
    return UpdateJsonAndConfig(true); // check proj_dir && save json
}

bool QDAProjectDetailDialog::UpdateJsonAndConfig(bool check_config)
{
    QString json_tmp = ui->viewProjectConfigText->toPlainText();
    // parse json_str to config and AddConfig();
    if (!QDAProjectConfig::AddConfigByString(json_tmp)) {
        return false;
    }

    QDAProjectConfig::ConfigInfo config = QDAProjectConfig::GetConfig();
    QString json_str = QDAProjectConfig::JsonStringFromConfig(config);
    ui->viewProjectConfigText->setPlainText(json_str);

    if (!QCKFile::SaveFile(config.json_file, json_str.toUtf8())) {
        QMessageBox::warning(NULL, "Save Config", "Save Json Config File Failed !");
        return false;
    }
    
    QString tips = "Save Json Config File : " + config.json_file + " succeed !";
    QMessageBox::information(NULL, "Save Config", tips);
    
    return true;
}
