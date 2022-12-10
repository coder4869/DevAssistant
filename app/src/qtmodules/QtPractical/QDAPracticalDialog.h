#ifndef QDA_PRACTICAL_DIALOG_H
#define QDA_PRACTICAL_DIALOG_H

#include <QDialog>

namespace Ui {
class QDAPracticalDialog;
}

class QDAPracticalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAPracticalDialog(QWidget *parent = nullptr);
    ~QDAPracticalDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnPracticalEncrypt();
    void OnPracticalDecrypt();
    
private:
    Ui::QDAPracticalDialog *ui;
};

#endif // QDA_PRACTICAL_DIALOG_H
