#ifndef QDA_PLAN_DIALOG_H
#define QDA_PLAN_DIALOG_H

#include <QDialog>

namespace Ui {
class QDAPlanDialog;
}

class QDAPlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAPlanDialog(QWidget *parent = nullptr);
    ~QDAPlanDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnPlanShow();
    
private:
    Ui::QDAPlanDialog *ui;
};

#endif // QDA_PLAN_DIALOG_H
