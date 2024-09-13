// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_ENCODE_H
#define QCK_ENCODE_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QString>
#include <QPixmap>
#include <QJsonDocument>

class QCKEncode
{
    Q_GADGET
    
public:
    explicit QCKEncode();
    ~QCKEncode();
   
    // base64
    /// @param imgFormat  bmp, png, jpg, jpeg, pbm ...
    static QByteArray Base64FromQImage(const QImage &image, const char* imgFormat);
    static QImage Base64ToQImage(const QByteArray &byteArray, const QString &imgSavePath = "");
    
    static QByteArray Base64FromQJson(const QJsonDocument &jsonDoc);
    static QJsonDocument Base64ToQJson(const QByteArray &byteArray);
    
private:
    
};

#endif /* QCK_ENCODE_H */
