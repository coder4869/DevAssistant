// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_HELP_DIALOG_H
#define QDA_HELP_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAHelpDialog;
}

class QDAHelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAHelpDialog(QWidget *parent = nullptr);
    ~QDAHelpDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnHelpShow();
    void OnShowVersion();

private:
    Ui::QDAHelpDialog *ui;
};

#endif // QDA_HELP_DIALOG_H
