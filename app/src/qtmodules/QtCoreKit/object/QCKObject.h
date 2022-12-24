#ifndef QCK_OBJECT_H
#define QCK_OBJECT_H

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
