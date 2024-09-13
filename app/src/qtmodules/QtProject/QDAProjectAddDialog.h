// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PROJECT_ADD_DIALOG_H
#define QDA_PROJECT_ADD_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAProjectAddDialog;
}

class QDAProjectAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAProjectAddDialog(QWidget *parent = nullptr);
    ~QDAProjectAddDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnProjectAddModule();
    void OnModuleAddClass();
    
private:
    Ui::QDAProjectAddDialog *ui;
};

#endif // QDA_PROJECT_ADD_DIALOG_H
