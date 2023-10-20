// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
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

#include "QDAPlanDialog.h"

#include <CLog/CAppConf.h>
#include <CUtils/CUFile.h>

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
    QUI::Style::SetPushButton(ui->loadPlanBtn);
    QUI::Style::SetPushButton(ui->savePlanBtn);

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
