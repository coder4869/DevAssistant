// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDACustomDialog.h"

#include <QMessageBox>
#include <QtUIInfra/QUIStyle.h>

#include "ui_QDACustomDialog.h"

QDACustomDialog::QDACustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDACustomDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setStyleSheet("QLabel { color:white; font:25px; }");
    QUI::Style::SetPushButton(ui->customScriptBtn);
}

QDACustomDialog::~QDACustomDialog()
{
    delete ui;
}


void QDACustomDialog::OnCustomShow()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Custom") , QStringLiteral("Show Custom View!"));
}
