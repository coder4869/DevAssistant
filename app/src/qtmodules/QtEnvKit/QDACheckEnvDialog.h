// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_CHECK_ENV_DIALOG_H
#define QDA_CHECK_ENV_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDACheckEnvDialog;
}

class QDACheckEnvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDACheckEnvDialog(QWidget *parent = nullptr);
    ~QDACheckEnvDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnCheckEnv();
    void OnTryFixEnvValue();

private:
    Ui::QDACheckEnvDialog *ui;
};

#endif // QDA_CHECK_ENV_DIALOG_H
