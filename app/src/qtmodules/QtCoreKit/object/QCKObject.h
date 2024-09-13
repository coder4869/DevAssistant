// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_OBJECT_H
#define QCK_OBJECT_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QObject>

class QCKObject
{
    Q_GADGET
    
public:
    explicit QCKObject();
    ~QCKObject();
    
    /// @brief DFS (Depth First Search)
    static QObject *ObjectNamed(QList<QObject*> objs, const QString &name);
    
private:
    
};

#endif /* QCK_OBJECT_H */
