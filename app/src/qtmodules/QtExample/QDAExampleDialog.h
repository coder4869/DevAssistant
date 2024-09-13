// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_EXAMPLE_DIALOG_H
#define QDA_EXAMPLE_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAExampleDialog;
}

class QDAExampleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAExampleDialog(QWidget *parent = nullptr);
    ~QDAExampleDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnExamplePreview();
    
private:
    Ui::QDAExampleDialog *ui;
};

#endif // QDA_EXAMPLE_DIALOG_H
