// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAProjectDetailDialog.h"

#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include <CUtils/logger.h>
#include <QtCoreKit/QtCoreKit.h>
#include <QtUIInfra/QUIStyle.h>
#include <QtEnvKit/DABuildScript.h>

#include "ui_QDAProjectDetailDialog.h"

QDAProjectDetailDialog::QDAProjectDetailDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAProjectDetailDialog)
{
//    QCKPython::InitPy();
    
    ui->setupUi(this);

    QUI::Style::SetPushButton(ui->createProjectBtn);
    connect(ui->createProjectBtn, SIGNAL(clicked(bool)), this, SLOT(OnCreate()));
    
    QUI::Style::SetPushButton(ui->loadProjectConfigBtn);
    connect(ui->loadProjectConfigBtn, SIGNAL(clicked(bool)), this, SLOT(OnLoadConfig()));

    QUI::Style::SetPushButton(ui->saveProjectConfigBtn);
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
        QMessageBox::critical(NULL, QStringLiteral("Project"), "TODO :: Show project Tree !");
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
    LOGI("App Dir Path = %s", dirPath.toUtf8().constData());
    QString pycmd = QCKCmd::GetPyBin() + "\"" + dirPath + "/../data/plugins/project/run.py\" --type project --config \"" + config.json_file + "\"";

    QByteArray output;
    QMessageBox::information(NULL, "pycmd", pycmd);
    bool ret = QCKCmd::ExecCmd(pycmd, QStringList(), output);
    if (!ret) {
        LOGE("pycmd = %s \n output=%s", pycmd.toUtf8().constData(), output.data());
        QMessageBox::critical(NULL, QStringLiteral("Project Create"), output.data());
        return;
    }

    // Note:: update build scripts
    QEK::BuildScript::GetInstance()->FixBuildScripts(config.proj_dir.toUtf8().constData());
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
