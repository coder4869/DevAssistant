// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_QML_UTIL_H
#define QCK_QML_UTIL_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QObject>

class QCKQmlUtil : public QObject 
{
    Q_OBJECT
    
public:
    explicit QCKQmlUtil(QObject *parent = nullptr);
    ~QCKQmlUtil();
    
private:
    
};

#endif /* QCK_QML_UTIL_H */
