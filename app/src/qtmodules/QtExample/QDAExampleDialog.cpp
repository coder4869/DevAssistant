// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAExampleDialog.h"

#include <QMessageBox>

#include "ui_QDAExampleDialog.h"

QDAExampleDialog::QDAExampleDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAExampleDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setStyleSheet("color:white;");
}

QDAExampleDialog::~QDAExampleDialog()
{
    delete ui;
}


void QDAExampleDialog::OnExamplePreview()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Example") , QStringLiteral("Example Preview!"));
}
