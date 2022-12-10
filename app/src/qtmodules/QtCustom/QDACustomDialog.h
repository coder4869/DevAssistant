#ifndef QDA_CUSTOM_DIALOG_H
#define QDA_CUSTOM_DIALOG_H

#include <QDialog>

namespace Ui {
class QDACustomDialog;
}

class QDACustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDACustomDialog(QWidget *parent = nullptr);
    ~QDACustomDialog();
    
Q_SIGNALS:
    void SigShowWidget(QWidget *widget);

public Q_SLOTS:
    void OnCustomShow();

private:
    Ui::QDACustomDialog *ui;
};

#endif // QDA_CUSTOM_DIALOG_H
