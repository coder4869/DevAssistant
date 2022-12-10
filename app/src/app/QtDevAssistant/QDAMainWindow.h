#ifndef QDA_MAINWINDOW_H
#define QDA_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QDAMainWindow; }
QT_END_NAMESPACE

class QDAMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QDAMainWindow(QWidget *parent = nullptr);
    ~QDAMainWindow();

private:
    Ui::QDAMainWindow *ui;
};
#endif // QDA_MAINWINDOW_H
