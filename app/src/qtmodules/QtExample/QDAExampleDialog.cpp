#include "QDAExampleDialog.h"

#include <QMessageBox>

#include "ui_QDAExampleDialog.h"

QDAExampleDialog::QDAExampleDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAExampleDialog)
{
    ui->setupUi(this);
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
