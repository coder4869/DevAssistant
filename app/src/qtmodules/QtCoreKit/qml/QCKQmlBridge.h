#ifndef QCK_QML_BRIDGE_H
#define QCK_QML_BRIDGE_H

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
