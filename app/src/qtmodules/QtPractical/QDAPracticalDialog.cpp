#include "QDAPracticalDialog.h"

#include <QMessageBox>

#include "ui_QDAPracticalDialog.h"

QDAPracticalDialog::QDAPracticalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAPracticalDialog)
{
    ui->setupUi(this);
}

QDAPracticalDialog::~QDAPracticalDialog()
{
    delete ui;
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
