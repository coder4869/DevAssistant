// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAHelpDialog.h"

#include <QMessageBox>
#include <QtUIInfra/QUIStyle.h>

#include "ui_QDAHelpDialog.h"

QDAHelpDialog::QDAHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAHelpDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setStyleSheet("QLabel { color:white; font:25px; }");
    QUI::Style::SetPushButton(ui->versionButton);
}

QDAHelpDialog::~QDAHelpDialog()
{
    delete ui;
}

void QDAHelpDialog::OnHelpShow()
{
    emit SigShowWidget(this);
//    QMessageBox::warning(NULL, QStringLiteral("Help") , QStringLiteral("Show Help View!"));
}

void QDAHelpDialog::OnShowVersion()
{
    std::string version = u8R"(
版本号(Version) : v1.1.4.0
   
日期(Date) : 2025/04/09
    )";
    QMessageBox::information(NULL, QStringLiteral("Version"), QString::fromStdString(version));
}
