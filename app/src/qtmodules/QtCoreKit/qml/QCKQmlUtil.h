#ifndef QCK_QML_UTIL_H
#define QCK_QML_UTIL_H

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
