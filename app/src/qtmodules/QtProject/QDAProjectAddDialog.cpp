// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAProjectAddDialog.h"

#include <QMessageBox>
#include <QtUIInfra/QUIStyle.h>

#include "ui_QDAProjectAddDialog.h"

QDAProjectAddDialog::QDAProjectAddDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAProjectAddDialog)
{
    ui->setupUi(this);

    QUI::Style::SetPushButton(ui->createProjectBtn);
}

QDAProjectAddDialog::~QDAProjectAddDialog()
{
    delete ui;
}

void QDAProjectAddDialog::OnProjectAddModule()
{
    emit SigShowWidget(this);
    
    QMessageBox::warning(NULL, QStringLiteral("ProjectAdd") , QStringLiteral("TODO :: OnProjectAddModule!"));
}

void QDAProjectAddDialog::OnModuleAddClass()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("ProjectAdd") , QStringLiteral("TODO :: OnModuleAddClass!"));
}
