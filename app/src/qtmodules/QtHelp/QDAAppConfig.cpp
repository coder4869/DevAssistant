// MIT License
//
// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
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

#include "QDAAppConfig.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDesktopServices>
#include <QMessageBox>

#include <CUtils/logger.h>
#include <CUtils/CUFile.h>
#include <CApp/CAppConf.h>
#include <QtCoreKit/QtCoreKit.h>

#define LOG_TAG "TAG_QtHelp"

static QDAAppConfig* instance = nullptr;
QDAAppConfig* QDAAppConfig::GetInstance()
{
    if (!instance) {
        instance = new QDAAppConfig();
    }
    return instance;
}

QDAAppConfig::QDAAppConfig() 
{

}

QDAAppConfig::~QDAAppConfig()
{

}

void QDAAppConfig::LoadConfig()
{
    std::string file_path = CKAppConf::GetInstance()->GetRelativePath("app_config", "/conf/app_config.json");
    std::string file_data = "";
    int ret = CU::File::LoadFileString(file_path, file_data);

    if (ret != 0) {
        file_data = file_path + " 文件解析失败！\n 请检查文件内容/编码等是否异常 ! ";
        LOGE("file_data = %s", file_data.c_str());
        return;
    }

    // check json data
    QJsonDocument json_doc = QJsonDocument::fromJson(file_data.c_str());
    if (json_doc.isEmpty() || !json_doc.isObject()) {
        QMessageBox::critical(NULL, __FUNCTION__, "Error json config ! Or Config is not an json object!");
        return;
    }

    // parse json key-values
    QJsonObject json_obj = json_doc.object();

    // docs
    if (json_obj.contains("docs")) {
        QJsonObject docs = json_obj["docs"].toObject();
        QStringList key = docs.keys();
        for (size_t idx = 0; idx < key.size(); idx++) {
            CKAppConf::GetInstance()->SetRelativePath(key[idx].toStdString(), docs[key[idx]].toString().toStdString());
        }
    }
}

