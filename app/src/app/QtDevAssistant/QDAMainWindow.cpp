#include "QDAMainWindow.h"
#include "ui_QDAMainWindow.h"

QDAMainWindow::QDAMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QDAMainWindow)
{
    ui->setupUi(this);
}

QDAMainWindow::~QDAMainWindow()
{
    delete ui;
}

