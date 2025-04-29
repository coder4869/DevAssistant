// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PROJECT_PKG_H
#define QDA_PROJECT_PKG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QDialog>

namespace Ui {
class QDAProjectPkg;
}
class QJsonArray;

class QDAProjectPkg : public QDialog
{
    Q_OBJECT

public:
    explicit QDAProjectPkg(QWidget *parent = nullptr);
    ~QDAProjectPkg();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnProjectPkg();
    void OnSelectPkgRootDir(bool);
    void OnPkgProcess(bool);

protected:
    bool CheckSubDirs(QJsonArray& sub_dirs);

private:
    Ui::QDAProjectPkg *ui;
};

#endif // QDA_PROJECT_PKG_H
