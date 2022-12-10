#ifndef QDA_HELP_DIALOG_H
#define QDA_HELP_DIALOG_H

#include <QDialog>

namespace Ui {
class QDAHelpDialog;
}

class QDAHelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDAHelpDialog(QWidget *parent = nullptr);
    ~QDAHelpDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnHelpShow();
    
private:
    Ui::QDAHelpDialog *ui;
};

#endif // QDA_HELP_DIALOG_H
