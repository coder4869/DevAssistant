#include "QDAProjectDialog.h"

#include <QMessageBox>

#include "ui_QDAProjectDialog.h"

QDAProjectDialog::QDAProjectDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::QDAProjectDialog)
{
    ui->setupUi(this);
}

QDAProjectDialog::~QDAProjectDialog()
{
    delete ui;
}


void QDAProjectDialog::OnCheckEnv()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Check Developping Environment!"));
}

void QDAProjectDialog::OnProjectCreate()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Create One New Project!"));
}

void QDAProjectDialog::OnProjectOpen()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Open One Existing Project!"));
}

void QDAProjectDialog::OnProjectView()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("View Existing Project Config!"));
}

void QDAProjectDialog::OnProjectAddModule()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Project Add One Module!"));
}

void QDAProjectDialog::OnModuleAddClass()
{
    emit SigShowWidget(this);
    QMessageBox::warning(NULL, QStringLiteral("Project") , QStringLiteral("Project Module add Class!"));
}

