// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QCKQmlBridge.h"

#include <QtQml>

QCKQmlBridge::QCKQmlBridge(QObject *parent) : QObject(parent)
{

}

QCKQmlBridge::~QCKQmlBridge()
{

}

void QCKQmlBridge::RegistQmlClass()
{
    qmlRegisterType<QCKQmlBridge>("QCKQmlBridge", 1, 0, "QCKQmlBridge");
}
