// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
