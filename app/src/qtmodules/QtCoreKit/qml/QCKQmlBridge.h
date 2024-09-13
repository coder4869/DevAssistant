// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_QML_BRIDGE_H
#define QCK_QML_BRIDGE_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QObject>

class QCKQmlBridge : public QObject 
{
    Q_OBJECT

public:
    explicit QCKQmlBridge(QObject *parent = nullptr);
    ~QCKQmlBridge();
    
    static void RegistQmlClass();
};

#endif /* QCK_QML_BRIDGE_H */
