#include "QDAPlanDialog.h"

#include <QMessageBox>

#include "ui_QDAPlanDialog.h"

QDAPlanDialog::QDAPlanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAPlanDialog)
{
    ui->setupUi(this);
}

QDAPlanDialog::~QDAPlanDialog()
{
    delete ui;
}

void QDAPlanDialog::OnPlanShow()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Plan") , QStringLiteral("Show Plan View!"));
}
