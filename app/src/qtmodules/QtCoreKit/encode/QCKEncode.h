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

#ifndef QCK_ENCODE_H
#define QCK_ENCODE_H

#include <CLog/CKDefines.h>

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
