// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAPracticalDialog.h"

#include <QMessageBox>
#include <QtUIInfra/QtUIInfra.h>

#include "ui_QDAPracticalDialog.h"

QDAPracticalDialog::QDAPracticalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAPracticalDialog)
{
    ui->setupUi(this);
    QUI::Style::SetDockWidget(ui->dockWidget);
    QUI::Style::SetTreeWidget(ui->optionsTreeWidget);
    connect(ui->optionsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(OnSetOption(QTreeWidgetItem *, int)));
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

void QDAPracticalDialog::OnSetOption(QTreeWidgetItem *item, int column)
{
    if (item == ui->optionsTreeWidget->topLevelItem(0)) {
        OnPracticalEncrypt();
    } else if (item == ui->optionsTreeWidget->topLevelItem(1)) {
        OnPracticalDecrypt();
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

void QDAPracticalDialog::SelectOptionTreeWidget(int index)
{
    ui->optionsTreeWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    for(int idx=0; idx<2; idx ++) {
        auto flag = QItemSelectionModel::SelectionFlag::Deselect;
        if (idx == index) {
            flag = QItemSelectionModel::SelectionFlag::Select;
        }
        ui->optionsTreeWidget->setCurrentItem(ui->optionsTreeWidget->topLevelItem(idx), 0, flag);
    }
}
