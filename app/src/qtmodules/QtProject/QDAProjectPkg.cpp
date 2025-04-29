// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAProjectPKG.h"

#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QStyleFactory>
#include <QDesktopServices>

#include <CUtils/logger.h>

#include <QtCoreKit/utils/QCKFile.h>
#include <QtCoreKit/script/QCKCmd.h>
#include <QtEnvKit/QtEnvKit.h>
#include <QtUIInfra/QtUIInfra.h>

#include "ui_QDAProjectPkg.h"

static const char* MSG_BOX_TIPS = u8"提示";
static const char* MSG_BOX_SET_ROOT_DIR = u8"请设置打包根目录！";
static const char* MSG_BOX_SET_SUB_DIRS = u8"请正确设置打包子目录！";
static const char* MSG_BOX_SET_SOFT_NAME = u8"请设置软件名称！";
static const char* MSG_BOX_PKG_SUCCESS = u8"安装包制作成功，即将打开根目录！";

QDAProjectPkg::QDAProjectPkg(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAProjectPkg)
{
    ui->setupUi(this);

    ui->rootDirEdit->setEnabled(false);
    ui->rootDirButton->setStyleSheet(QUI::Style::PushButton());
    connect(ui->rootDirButton, SIGNAL(clicked(bool)), this, SLOT(OnSelectPkgRootDir(bool)));

    ui->pkgButton->setStyleSheet(QUI::Style::PushButton());
    connect(ui->pkgButton, SIGNAL(clicked(bool)), this, SLOT(OnPkgProcess(bool)));
}

QDAProjectPkg::~QDAProjectPkg()
{
    delete ui;
}

void QDAProjectPkg::OnProjectPkg()
{
    emit SigShowWidget(this);
}

void QDAProjectPkg::OnSelectPkgRootDir(bool)
{
    QStringList list = QCKFile::SelectDirectory(false);
    if (list.size() == 1) {
        LOGI("select dir: %s", list[0].toStdString().c_str());
        ui->rootDirEdit->setText(list[0]);
    } else {
        LOGI("not select any dir!");
    }
}

void QDAProjectPkg::OnPkgProcess(bool)
{
    // ui->rootDirEdit
    if (ui->rootDirEdit->text().isEmpty()) {
        QMessageBox msgBox;
        int ret = QUI::Style::ShowMsgBox(msgBox, QMessageBox::Critical, MSG_BOX_TIPS, MSG_BOX_SET_ROOT_DIR, true);
        return;
    }

    // ui->subDirsEdit
    QJsonArray sub_dirs;
    if (!CheckSubDirs(sub_dirs)) {
        QMessageBox msgBox;
        int ret = QUI::Style::ShowMsgBox(msgBox, QMessageBox::Critical, MSG_BOX_TIPS, MSG_BOX_SET_SUB_DIRS, true);
        return;
    }

    // ui->softNameEdit
    if (ui->softNameEdit->text().isEmpty()) {
        QMessageBox msgBox;
        int ret = QUI::Style::ShowMsgBox(msgBox, QMessageBox::Critical, MSG_BOX_TIPS, MSG_BOX_SET_SOFT_NAME, true);
        return;
    }

    QJsonObject cfg_obj;
    cfg_obj["root_dir"] = ui->rootDirEdit->text();
    cfg_obj["pkg_dirs"] = sub_dirs;
    cfg_obj["proj_name"] = ui->softNameEdit->text();
    cfg_obj["script_dir"] = u8"scripts";

    QString script_dir_path = ui->rootDirEdit->text() + "/scripts";
    QDir script_dir(script_dir_path);
    if (!script_dir.exists()) {
        script_dir.mkpath(script_dir_path);
    }

    // ui->softVersionEdit
    if (!ui->softVersionEdit->text().isEmpty()) {
        cfg_obj["version"] = ui->softVersionEdit->text();
    }

    // ui->softDescEdit
    if (!ui->softDescEdit->toPlainText().isEmpty()) {
        cfg_obj["describe"] = ui->softDescEdit->toPlainText();
    }

    QString pkg_json_path = ui->rootDirEdit->text() + "/pkg.json";
    QString json_str = QString(QJsonDocument(cfg_obj).toJson());
    if (!QCKFile::SaveFile(pkg_json_path, json_str.toUtf8())) {
        QMessageBox::warning(NULL, "Save Pkg Json Config", "Save Json Config File Failed !");
    }

    // TODO::显示旋转框
    // call pkg python
    QString dirPath = QCoreApplication::applicationDirPath();
    LOGI("App Dir Path = %s", dirPath.toUtf8().constData());
    QString pycmd = QCKCmd::GetPyBin() + "\"" + dirPath + "/../data/plugins/project/proj_pkg/run_pkg.py\" --config \"" + pkg_json_path + "\"";

    QByteArray output;
    QMessageBox::information(NULL, "pycmd", pycmd);
    bool ret = QCKCmd::ExecCmd(pycmd, QStringList(), output);
    // TODO::关闭旋转框
    if (!ret) {
        LOGE("project pkg pycmd = %s \n output=%s", pycmd.toUtf8().constData(), output.data());
        QMessageBox::critical(NULL, QStringLiteral("Project Pkg"), output.data());
        return;
    }

    LOGI("project pkg pycmd = %s", pycmd.toUtf8().constData());
    QMessageBox msgBox;
    int ret1 = QUI::Style::ShowMsgBox(msgBox, QMessageBox::Information, MSG_BOX_TIPS, MSG_BOX_PKG_SUCCESS, true);
    if (ret1 == QMessageBox::Ok) {
        QUrl url = QUrl::fromLocalFile(ui->rootDirEdit->text());
        QDesktopServices::openUrl(url);
    }
}

bool QDAProjectPkg::CheckSubDirs(QJsonArray &sub_dirs)
{
    QString str = ui->subDirsEdit->text();
    if (str.isEmpty()) {
        return false;
    }

    QString root_dir = ui->rootDirEdit->text();
    // seperate && check subdirs
    QStringList dirs = str.split(",");
    for (size_t idx = 0; idx < dirs.size(); idx++) {
        QString dir_name = dirs[idx].trimmed();
        QDir dir(root_dir + "/" + dir_name);
        if (dir.exists()) {
            sub_dirs.append(dir_name);
        } else {
            LOGI("dir %s not exist!", (root_dir + "/" + dir_name).toStdString().c_str());
        }
    }
    return !sub_dirs.empty();
}
