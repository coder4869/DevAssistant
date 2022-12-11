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

#include "QDAPracticalDialog.h"

#include <QMessageBox>

#include "ui_QDAPracticalDialog.h"

QDAPracticalDialog::QDAPracticalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAPracticalDialog)
{
    ui->setupUi(this);
    ui->dockWidget->setWindowFlag(Qt::FramelessWindowHint);
    ui->dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
}

QDAPracticalDialog::~QDAPracticalDialog()
{
    delete ui;
}

void QDAPracticalDialog::OnSetContextWidget(QWidget *widget)
{
    if (widget) {
        ui->dockWidget->setWidget(widget);
        widget->setEnabled(true);
        widget->show();
    }
}

void QDAPracticalDialog::OnPracticalEncrypt()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Practical") , QStringLiteral("Encrypt!"));
}

void QDAPracticalDialog::OnPracticalDecrypt()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Practical") , QStringLiteral("Decrypt!"));
}
