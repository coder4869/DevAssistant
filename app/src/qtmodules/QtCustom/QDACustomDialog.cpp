#include "QDACustomDialog.h"

#include <QMessageBox>

#include "ui_QDACustomDialog.h"

QDACustomDialog::QDACustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDACustomDialog)
{
    ui->setupUi(this);
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
