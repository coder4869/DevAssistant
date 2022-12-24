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
