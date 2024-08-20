// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "QDAMainWindow.h"
#include "ui_QDAMainWindow.h"

#include <QWindowStateChangeEvent>
#include <QMessageBox>

#include <iostream>
#ifdef WIN
#include <windows.h>
#endif // WIN

#include <CUtils/log.h>
#include <COSEnv/CETrayIcon.h>

#include <QtProject/QtProject.h>
#include <QtExample/QtExample.h>
#include <QtPractical/QtPractical.h>
#include <QtCustom/QtCustom.h>
#include <QtPlan/QtPlan.h>
#include <QtHelp/QtHelp.h>

#include <QtUIInfra/QtUIInfra.h>

QDAMainWindow::QDAMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QDAMainWindow)
{
    ui->setupUi(this);
    setMinimumSize(1280, 720);
    QUI::Style::SetMainWindow(this);

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
    //connect(help, SIGNAL(SigShowWidget(QWidget *)), this, SLOT(OnSetCentralWidget(QWidget *)));
    connect(ui->actionVersion, SIGNAL(triggered()), help, SLOT(OnShowVersion()));

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
    //delete help;
    delete ui;
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

void QDAMainWindow::LoadWelcome()
{
    project->OnCheckEnv();
}

/////////////////////////////////////// TrayIcon Section ///////////////////////////////////////

bool QDAMainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
#ifdef WIN
    MSG* msg = (MSG*)message;
    if (msg->message == WM_TO_TRAY) {
        LOG_INFO << " eventType = " << QString(eventType).toStdString() << std::endl;
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
    LOG_INFO << " event->type() = " << event->type() << std::endl;
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
