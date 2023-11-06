// MIT License
//
// Copyright (c) 2021~2023 [coder4869](https://github.com/coder4869)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

