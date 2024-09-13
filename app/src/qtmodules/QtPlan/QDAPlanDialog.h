// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PLAN_DIALOG_H
#define QDA_PLAN_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAPlanDialog;
}

class QDAPlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAPlanDialog(QWidget *parent = nullptr);
    ~QDAPlanDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnPlanShow();
    void OnLoadPlan();
    void OnSavePlan();
    
private:
    Ui::QDAPlanDialog *ui;
};

#endif // QDA_PLAN_DIALOG_H
