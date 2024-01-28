// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
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

#ifndef QDA_PROJECT_DIALOG_H
#define QDA_PROJECT_DIALOG_H

#include <CLog/CKDefines.h>

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
    void OnProjectAddModule();
    void OnModuleAddClass();
    
private:
    Ui::QDAProjectDialog *ui;
    QDACheckEnvDialog *check_env;
    QDAProjectDetailDialog *project_detail;
    QDAProjectAddDialog *project_add;
    
    void SelectOptionTreeWidget(int index);
};

#endif // QDA_PROJECT_DIALOG_H
