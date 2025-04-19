// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAMainWindow.h"
#include "ui_QDAMainWindow.h"

#include <QWindowStateChangeEvent>
#include <QMessageBox>
#include <QStyle>

#include <iostream>
#if WIN
#include <windows.h>
#endif // WIN

#include <CUtils/logger.h>
#include <COSEnv/CETrayIcon.h>

#include <QtProject/QtProject.h>
#include <QtExample/QtExample.h>
#include <QtPractical/QtPractical.h>
#include <QtCustom/QtCustom.h>
#include <QtPlan/QtPlan.h>
#include <QtHelp/QtHelp.h>

#include <QtUIInfra/QtUIInfra.h>

#define LOG_TAG "TAG_DevAssistant"

QDAMainWindow::QDAMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QDAMainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1280, 720);
    setStyleSheet(QUI::Style::MainWindowStyle());
    initWidget = centralWidget();

    // QDAProjectDialog
    project = new QDAProjectDialog();
    connect(project, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionEnvCheck, SIGNAL(triggered()), project, SLOT(OnCheckEnv()));
    connect(ui->actionProjectNew, SIGNAL(triggered()), project, SLOT(OnProjectCreate()));
    connect(ui->actionProjectOpen, SIGNAL(triggered()), project, SLOT(OnProjectOpen()));
    connect(ui->actionProjectReview, SIGNAL(triggered()), project, SLOT(OnProjectView()));

    // QDAExampleDialog
    example = new QDAExampleDialog();
    connect(example, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionExampleView, SIGNAL(triggered()), example, SLOT(OnExamplePreview()));

    // QDAPracticalDialog
    practical = new QDAPracticalDialog();
    connect(practical, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    //connect(ui->actionEncrypt, SIGNAL(triggered()), practical, SLOT(OnPracticalEncrypt()));
    //connect(ui->actionDecrypt, SIGNAL(triggered()), practical, SLOT(OnPracticalDecrypt()));
    
    // QDACustomDialog
    custom = new QDACustomDialog();
    connect(custom, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    //connect(ui->actionCustom, SIGNAL(triggered()), custom, SLOT(OnCustomShow()));

    // QDAPlanDialog
    plan = new QDAPlanDialog();
    connect(plan, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionPlan, SIGNAL(triggered()), plan, SLOT(OnPlanShow()));

    // QDAHelpDialog
    help = new QDAHelpDialog();
    //connect(help, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionVersion, SIGNAL(triggered()), help, SLOT(OnShowVersion()));
    connect(ui->actionWelcome, SIGNAL(triggered()), this, SLOT(OnSetWelcome()));

    // Basic Functions
    ui->envCheckButton->setStyleSheet(QUI::Style::PushButtonCyan());
    ui->projGenButton->setStyleSheet(QUI::Style::PushButtonCyan());
    ui->pkgGenButton->setStyleSheet(QUI::Style::PushButtonCyan());
    //ui->envCheckButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogListView));
    //ui->projGenButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogListView));
    connect(ui->envCheckButton, SIGNAL(clicked(bool)), project, SLOT(OnCheckEnv()));
    connect(ui->projGenButton, SIGNAL(clicked(bool)), project, SLOT(OnProjectCreate()));

    // Extend Functions
    ui->dataEncryptButton->setStyleSheet(QUI::Style::PushButtonCyan());
    ui->dataDecryptButton->setStyleSheet(QUI::Style::PushButtonCyan());
    connect(ui->dataEncryptButton, SIGNAL(clicked(bool)), practical, SLOT(OnPracticalEncrypt()));
    connect(ui->dataDecryptButton, SIGNAL(clicked(bool)), practical, SLOT(OnPracticalDecrypt()));

    QDAAppConfig::GetInstance()->LoadConfig();

    CE::TrayIcon::SetIcon(winId(), "IDI_ICON1", "开发助手", 0);
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

void QDAMainWindow::OnSetWelcome()
{
    OnSetCentralWidget(initWidget);
}

void QDAMainWindow::OnSetCentralWidget(QWidget *widget)
{
    // remove old
    takeCentralWidget();
    
    // set New
    setCentralWidget(widget);
    widget->setEnabled(true);
    widget->show();
}


/////////////////////////////////////// TrayIcon Section ///////////////////////////////////////

bool QDAMainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
#if WIN
    MSG* msg = (MSG*)message;
    if (msg->message == WM_TO_TRAY) {
        LOGI("eventType = %s", QString(eventType).toStdString().c_str());
        if (msg->lParam == WM_LBUTTONUP) { // Left Button Double Click        
            CE::TrayIcon::ShowWindow(winId(), true);
            showMaximized(); // Required
        }
        //else if (msg->lParam == WM_LBUTTONDBLCLK) { // Left Button Double Click        
        //    //CE::TrayIcon::DelIcon(winId());
        //}
    }
#endif // WIN

    return QWidget::nativeEvent(eventType, message, result);
}

void QDAMainWindow::changeEvent(QEvent * event)
{
    LOGI("event->type() = %d", event->type());
    if (QEvent::WindowStateChange == event->type())
    {
        QWindowStateChangeEvent * stateEvent = dynamic_cast<QWindowStateChangeEvent*>(event);
        if (Q_NULLPTR != stateEvent) {
            Qt::WindowStates x = stateEvent->oldState();
            if (Qt::WindowMinimized == stateEvent->oldState()) {
                CE::TrayIcon::ShowWindow(winId(), true);
                showMaximized(); // Required
            }
            else if (Qt::WindowMaximized == stateEvent->oldState()) {
                CE::TrayIcon::ShowWindow(winId(), false);
            }
        }
    }
    else if (QEvent::Quit == event->type()) {
        CE::TrayIcon::DelIcon(winId());
    }
}
