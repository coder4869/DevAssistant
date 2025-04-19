// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QDAPlanDialog.h"

#include <CUtils/CUFile.h>
#include <CApp/CAppConf.h>

#include <QPushButton>
#include <QMessageBox>
#include <QtUIInfra/QUIStyle.h>
#include <QtHelp/QDAAppConfig.h>

#include "ui_QDAPlanDialog.h"

QDAPlanDialog::QDAPlanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDAPlanDialog)
{
    ui->setupUi(this);
    ui->titleLabel->setStyleSheet("QLabel { color:white; font:25px; }");
    ui->loadPlanBtn->setStyleSheet(QUI::Style::PushButton());
    ui->savePlanBtn->setStyleSheet(QUI::Style::PushButton());

    connect(ui->loadPlanBtn, SIGNAL(clicked(bool)), this, SLOT(OnLoadPlan()));
    connect(ui->savePlanBtn, SIGNAL(clicked(bool)), this, SLOT(OnSavePlan()));
}

QDAPlanDialog::~QDAPlanDialog()
{
    delete ui;
}

void QDAPlanDialog::OnPlanShow()
{
    emit SigShowWidget(this);
    OnLoadPlan();
}

void QDAPlanDialog::OnLoadPlan() 
{
    std::string file_path = CKAppConf::GetInstance()->GetRelativePath("plan");
    std::string file_data = "";
    int ret = CU::File::LoadFileString(file_path, file_data);

    ui->viewPlanText->setPlainText(QString::fromStdString((ret != 0) ? u8"规划文件加载失败 : \n" + file_path : file_data));
}

void QDAPlanDialog::OnSavePlan()
{
    std::string content = ui->viewPlanText->toPlainText().toStdString();

    //auto tmp_str = content.substr(0, content.length()-1);
    //tmp_str.append("}");
    std::string save_path = CKAppConf::GetInstance()->GetRelativePath("plan");
    int ret = CU::File::SaveFileString(save_path, content);
    QMessageBox::warning(NULL, QStringLiteral("Plan"), QString::fromStdString(save_path));

}
