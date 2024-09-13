// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_CUSTOM_DIALOG_H
#define QDA_CUSTOM_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDACustomDialog;
}

class QDACustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDACustomDialog(QWidget *parent = nullptr);
    ~QDACustomDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnCustomShow();

private:
    Ui::QDACustomDialog *ui;
};

#endif // QDA_CUSTOM_DIALOG_H
