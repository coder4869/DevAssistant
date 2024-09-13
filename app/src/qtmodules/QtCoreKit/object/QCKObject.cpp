// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QCKObject.h"

QCKObject::QCKObject()
{

}

QCKObject::~QCKObject()
{

}

/// @brief DFS (Depth First Search)
QObject *QCKObject::ObjectNamed(QList<QObject*> objs, const QString &name)
{
    for (size_t idx=0; idx<objs.size(); idx++) {
        QObject *obj_item = objs.at(idx);
        if (obj_item->objectName() == name) {
            return obj_item;
        }
        
        QObject *child_obj = ObjectNamed(obj_item->children(), name);
        if (child_obj) {
            return child_obj;
        }
    }
    return nullptr;
}
