#include "QDAMainWindow.h"
#include "ui_QDAMainWindow.h"

#include <QtProject/QtProject.h>
#include <QtExample/QtExample.h>
#include <QtPractical/QtPractical.h>
#include <QtCustom/QtCustom.h>
#include <QtPlan/QtPlan.h>
#include <QtHelp/QtHelp.h>

QDAMainWindow::QDAMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QDAMainWindow)
{
    ui->setupUi(this);
    
    // QDAProjectDialog
    project = new QDAProjectDialog();
    connect(project, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionEnvCheck, SIGNAL(triggered()), project, SLOT(OnCheckEnv()));
    connect(ui->actionProjectNew, SIGNAL(triggered()), project, SLOT(OnProjectCreate()));
    connect(ui->actionProjectOpen, SIGNAL(triggered()), project, SLOT(OnProjectOpen()));
    connect(ui->actionProjectReview, SIGNAL(triggered()), project, SLOT(OnProjectView()));
    connect(ui->actionModuleAdd, SIGNAL(triggered()), project, SLOT(OnProjectAddModule()));
    connect(ui->actionClassAdd, SIGNAL(triggered()), project, SLOT(OnModuleAddClass()));
    
    // QDAExampleDialog
    example = new QDAExampleDialog();
    connect(example, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionExampleView, SIGNAL(triggered()), example, SLOT(OnExamplePreview()));

    // QDAPracticalDialog
    practical = new QDAPracticalDialog();
    connect(practical, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionEncrypt, SIGNAL(triggered()), practical, SLOT(OnPracticalEncrypt()));
    connect(ui->actionDecrypt, SIGNAL(triggered()), practical, SLOT(OnPracticalDecrypt()));
    
    // QDACustomDialog
    custom = new QDACustomDialog();
    connect(custom, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionCustom, SIGNAL(triggered()), custom, SLOT(OnCustomShow()));

    // QDAPlanDialog
    plan = new QDAPlanDialog();
    connect(plan, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionPlan, SIGNAL(triggered()), plan, SLOT(OnPlanShow()));

    // QDAHelpDialog
    help = new QDAHelpDialog();
    connect(help, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionVersion, SIGNAL(triggered()), help, SLOT(OnHelpShow()));
}

QDAMainWindow::~QDAMainWindow()
{
    delete project;
    delete example;
    delete practical;
    delete custom;
    delete plan;
    delete help;
    delete ui;
}

void QDAMainWindow::OnSetCentralWidget(QWidget *widget)
{
    setCentralWidget(widget);
    widget->setEnabled(true);
    widget->show();
}
