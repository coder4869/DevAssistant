#include "QCKQmlEngine.h"

#include "object/QCKObject.h"

QCKQmlEngine::QCKQmlEngine(QCKQmlEngine *parent) 
{

}

QCKQmlEngine::~QCKQmlEngine()
{

}

QQmlApplicationEngine *QCKQmlEngine::NewAppEngine(const QString &qmlPath)
{
    QQmlApplicationEngine *engine = new QQmlApplicationEngine();
    engine->load(QUrl(qmlPath));
    return engine;
}

QObject *QCKQmlEngine::ObjFromAppEngine(QQmlApplicationEngine *engine, const QString &name)
{
    if (engine) {
        return QCKObject::ObjectNamed(engine->rootObjects(), name);;
    }
    return nullptr;
}
