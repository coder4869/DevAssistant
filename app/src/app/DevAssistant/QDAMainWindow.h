// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_MAINWINDOW_H
#define QDA_MAINWINDOW_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QMainWindow>

namespace Ui {
class QDAMainWindow;
}
class QDAProjectDialog;
class QDAExampleDialog;
class QDAPracticalDialog;
class QDACustomDialog;
class QDAPlanDialog;
class QDAHelpDialog;

class QDAMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QDAMainWindow(QWidget *parent = nullptr);
    virtual ~QDAMainWindow();
    
    void LoadWelcome();

public Q_SLOTS:
    void OnSetWelcome();
    void OnSetCentralWidget(QWidget *widget);

private:
    Ui::QDAMainWindow *ui;
    QDAProjectDialog *project;
    QDAExampleDialog *example;
    QDAPracticalDialog *practical;
    QDACustomDialog *custom;
    QDAPlanDialog *plan;
    QDAHelpDialog *help;
    QWidget* initWidget;

protected:
    ////////////////////////// TrayIcon Section //////////////////////////
    virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
    virtual void changeEvent(QEvent* event) override;
};

#endif // QDA_MAINWINDOW_H
