#include "QDAHelpDialog.h"

#include <QMessageBox>

#include "ui_QDAHelpDialog.h"

QDAHelpDialog::QDAHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAHelpDialog)
{
    ui->setupUi(this);
}

QDAHelpDialog::~QDAHelpDialog()
{
    delete ui;
}

void QDAHelpDialog::OnHelpShow()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Help") , QStringLiteral("Show Help View!"));
}
