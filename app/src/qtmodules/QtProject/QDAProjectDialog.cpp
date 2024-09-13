// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAProjectDialog.h"

#include <QMessageBox>
#include <QStyleFactory>

#include <QtEnvKit/QtEnvKit.h>
#include <QtUIInfra/QtUIInfra.h>

#include "ui_QDAProjectDialog.h"
#include "QDAProjectDetailDialog.h"
#include "QDAProjectAddDialog.h"

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
    QUI::Style::SetDockWidget(ui->dockWidget);
    QUI::Style::SetTreeWidget(ui->optionsTreeWidget);
    connect(ui->optionsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(OnSetOption(QTreeWidgetItem *, int)));
    
    // QDACheckEnvDialog
    check_env = new QDACheckEnvDialog();
    connect(check_env, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetContextWidget(QWidget *)));
    
    // QDAProjectDetailDialog
    project_detail = new QDAProjectDetailDialog();
    connect(project_detail, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetContextWidget(QWidget *)));
 
    // QDAProjectAddDialog
    project_add = new QDAProjectAddDialog();
    connect(project_add, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetContextWidget(QWidget *)));

}

QDAProjectDialog::~QDAProjectDialog()
{
    delete check_env;
    delete project_detail;
    delete project_add;
    delete ui;
}

void QDAProjectDialog::OnSetContextWidget(QWidget *widget)
{
    if (widget) {
        // remove old
        QWidget *old = ui->dockWidget->widget();
        old->setParent(nullptr);
        old->hide();
        
        ui->dockWidget->setWidget(widget);
        widget->setEnabled(true);
        widget->show();
    }
}

void QDAProjectDialog::OnSetOption(QTreeWidgetItem *item, int column)
{
    if (item == ui->optionsTreeWidget->topLevelItem(QDAProjectOptions::CheckEnv)) {
        OnCheckEnv();
    } else if (item == ui->optionsTreeWidget->topLevelItem(QDAProjectOptions::Create)) {
        OnProjectCreate();
    } else if (item == ui->optionsTreeWidget->topLevelItem(QDAProjectOptions::Open)) {
        OnProjectOpen();
    } else if (item == ui->optionsTreeWidget->topLevelItem(QDAProjectOptions::View)) {
        OnProjectView();
    } else if (item == ui->optionsTreeWidget->topLevelItem(QDAProjectOptions::AddModule)) {
        OnProjectAddModule();
    } else if (item == ui->optionsTreeWidget->topLevelItem(QDAProjectOptions::AddClass)) {
        OnModuleAddClass();
    }
}

void QDAProjectDialog::OnCheckEnv()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::CheckEnv);
    check_env->OnCheckEnv();
}

void QDAProjectDialog::OnProjectCreate()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::Create);
    project_detail->OnProjectCreate();
}

void QDAProjectDialog::OnProjectOpen()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::Open);
    project_detail->OnProjectOpen();
}

void QDAProjectDialog::OnProjectView()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::View);
    project_detail->OnProjectView();
}

void QDAProjectDialog::OnProjectAddModule()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::AddModule);
    project_add->OnProjectAddModule();
}

void QDAProjectDialog::OnModuleAddClass()
{
    emit SigShowWidget(this);
    SelectOptionTreeWidget(QDAProjectOptions::AddClass);
    project_add->OnModuleAddClass();
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
