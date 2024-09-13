// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PRACTICAL_DIALOG_H
#define QDA_PRACTICAL_DIALOG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAPracticalDialog;
}
class QTreeWidgetItem;

class QDAPracticalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAPracticalDialog(QWidget *parent = nullptr);
    ~QDAPracticalDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnSetContextWidget(QWidget *widget);
    void OnSetOption(QTreeWidgetItem *item, int column);

    void OnPracticalEncrypt();
    void OnPracticalDecrypt();
    
private:
    Ui::QDAPracticalDialog *ui;
    void SelectOptionTreeWidget(int index);
};

#endif // QDA_PRACTICAL_DIALOG_H
