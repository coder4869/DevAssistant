#ifndef QCK_QML_ENGINE_H
#define QCK_QML_ENGINE_H

#include <QQmlApplicationEngine>

class QCKQmlEngine
{
    Q_GADGET
    
public:
    explicit QCKQmlEngine(QCKQmlEngine *parent = nullptr);
    ~QCKQmlEngine();
    
    static QQmlApplicationEngine *NewAppEngine(const QString &qmlPath);
    static QObject *ObjFromAppEngine(QQmlApplicationEngine *engine, const QString &name);
    
private:
    
};

#endif /* QCK_QML_ENGINE_H */
