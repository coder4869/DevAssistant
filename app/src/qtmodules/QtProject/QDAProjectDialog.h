#ifndef QDA_PROJECT_DIALOG_H
#define QDA_PROJECT_DIALOG_H

#include <QDialog>

namespace Ui {
class QDAProjectDialog;
}

class QDAProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAProjectDialog(QWidget *parent = nullptr);
    ~QDAProjectDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnCheckEnv();
    void OnProjectCreate();
    void OnProjectOpen();
    void OnProjectView();
    void OnProjectAddModule();
    void OnModuleAddClass();
    
private:
    Ui::QDAProjectDialog *ui;
};

#endif // QDA_PROJECT_DIALOG_H
