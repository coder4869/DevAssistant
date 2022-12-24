#include "QCKEncode.h"

#include <QBuffer>
#include <QByteArray>

QCKEncode::QCKEncode()
{

}

QCKEncode::~QCKEncode()
{

}

/// @param imgFormat  bmp, png, jpg, jpeg, pbm ...
QByteArray QCKEncode::Base64FromQImage(const QImage &image, const char* imgFormat)
{
    QByteArray byte_array;
    QBuffer buf(&byte_array);
    image.save(&buf, imgFormat);
    QByteArray base64_byte_array = byte_array.toBase64();
    buf.close();
    return base64_byte_array;
}

QImage QCKEncode::Base64ToQImage(const QByteArray &byteArray, const QString &imgSavePath)
{
    QByteArray img_byte_array = QByteArray::fromBase64(byteArray);
    QBuffer buffer(&img_byte_array);
    buffer.open(QIODevice::WriteOnly);
    QImage image;
    image.loadFromData(img_byte_array);
    buffer.close();
    
    if (imgSavePath != "") {
        image.save(imgSavePath);
    }
    
    return image;
}

QByteArray QCKEncode::Base64FromQJson(const QJsonDocument &jsonDoc)
{
    QByteArray json = jsonDoc.toJson();
    QByteArray json_byte_array = json.toBase64();
    return json_byte_array;
}

QJsonDocument QCKEncode::Base64ToQJson(const QByteArray &byteArray)
{
    QByteArray json_byte_array = QByteArray::fromBase64(byteArray);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json_byte_array);
    return jsonDoc;
}

