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

#include "QDAProjectDialog.h"

#include <QMessageBox>

#include "ui_QDAProjectDialog.h"
#include "QDACheckEnvDialog.h"

enum QDAProjectOptions : int {
    CheckEnv = 0,
    Create,
    Open,
    View,
    AddModule,
    AddClass,
    Unkonwn
};

QDAProjectDialog::QDAProjectDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAProjectDialog)
{
    ui->setupUi(this);
    ui->dockWidget->setWindowFlag(Qt::FramelessWindowHint);
    ui->dockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    checkEnv = new QDACheckEnvDialog(this);
    connect(checkEnv, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetContextWidget(QWidget *)));
}

QDAProjectDialog::~QDAProjectDialog()
{
    delete checkEnv;
    delete ui;
}

void QDAProjectDialog::OnSetContextWidget(QWidget *widget)
{
    if (widget) {
        ui->dockWidget->setWidget(widget);
        widget->setEnabled(true);
        widget->show();
    }
}

void QDAProjectDialog::OnCheckEnv()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::CheckEnv);
    checkEnv->OnCheckEnv();
}

void QDAProjectDialog::OnProjectCreate()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::Create);
    
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Create One New Project!"));
}

void QDAProjectDialog::OnProjectOpen()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::Open);

    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Open One Existing Project!"));
}

void QDAProjectDialog::OnProjectView()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::View);

    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("View Existing Project Config!"));
}

void QDAProjectDialog::OnProjectAddModule()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::AddModule);

    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Project Add One Module!"));
}

void QDAProjectDialog::OnModuleAddClass()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::AddClass);

    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Project Module add Class!"));
}

void QDAProjectDialog::SelectOptionTreeWidget(int index)
{
    ui->optionsTreeWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    for(int idx=0; idx<QDAProjectOptions::Unkonwn; idx ++) {
        auto flag = QItemSelectionModel::SelectionFlag::Deselect;
        if (idx == index) {
            flag = QItemSelectionModel::SelectionFlag::Select;
        }
        ui->optionsTreeWidget->setCurrentItem(ui->optionsTreeWidget->topLevelItem(idx), 0, flag);
    }
}
