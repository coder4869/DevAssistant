#ifndef QDA_MAINWINDOW_H
#define QDA_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QDAMainWindow;
}
class QDAProjectDialog;
class QDAExampleDialog;
class QDAPracticalDialog;
class QDACustomDialog;
class QDAPlanDialog;
class QDAHelpDialog;
QT_END_NAMESPACE

class QDAMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QDAMainWindow(QWidget *parent = nullptr);
    ~QDAMainWindow();
    
public Q_SLOTS:
    void OnSetCentralWidget(QWidget *widget);
    
private:
    Ui::QDAMainWindow *ui;
    QDAProjectDialog *project;
    QDAExampleDialog *example;
    QDAPracticalDialog *practical;
    QDACustomDialog *custom;
    QDAPlanDialog *plan;
    QDAHelpDialog *help;
};

#endif // QDA_MAINWINDOW_H
