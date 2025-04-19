// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PROJECT_DIALOG_H
#define QDA_PROJECT_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAProjectDialog;
}
class QTreeWidgetItem;
class QDACheckEnvDialog;
class QDAProjectDetailDialog;
class QDAProjectAddDialog;

class QDAProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAProjectDialog(QWidget *parent = nullptr);
    ~QDAProjectDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnSetContextWidget(QWidget *widget);
    void OnSetOption(QTreeWidgetItem *item, int column);
    
    void OnCheckEnv();
    void OnProjectCreate();
    void OnProjectOpen();
    void OnProjectView();
    void OnProjectAddModule();  // unused
    void OnModuleAddClass();    // unused
    
private:
    Ui::QDAProjectDialog *ui;
    QDACheckEnvDialog *check_env;
    QDAProjectDetailDialog *project_detail;
    QDAProjectAddDialog *project_add;
    
    void SelectOptionTreeWidget(int index);
};

#endif // QDA_PROJECT_DIALOG_H
