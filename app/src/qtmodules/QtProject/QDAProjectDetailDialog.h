// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PROJECT_DETAIL_DIALOG_H
#define QDA_PROJECT_DETAIL_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>
#include "QDAProjectConfig.h"

namespace Ui {
class QDAProjectDetailDialog;
}

class QDAProjectDetailDialog : public QDialog
{
    Q_OBJECT

public:
    enum class ShowMode {
        Add,
        Open,
        View
    };
    
    explicit QDAProjectDetailDialog(QWidget *parent = nullptr);
    ~QDAProjectDetailDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnProjectCreate();
    void OnProjectOpen();
    void OnProjectView();
    
protected Q_SLOTS:
    void OnCreate();
    bool OnLoadConfig();
    bool OnSaveConfig();

private:
    bool UpdateJsonAndConfig(bool check_config);

private:
    Ui::QDAProjectDetailDialog *ui;
    ShowMode show_mode;
    bool is_view_avaliable = false;
};

#endif // QDA_PROJECT_DETAIL_DIALOG_H
