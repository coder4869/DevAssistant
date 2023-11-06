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

#include "QDAProjectConfig.h"

#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>

#include <QtCoreKit/QtCoreKit.h>

const char* PROJECT_CONF_JSON = "/conf/project.json";

QMap<QDAProjectConfig::JsonType, QString> QDAProjectConfig::json_config_files;
QDAProjectConfig::ConfigInfo QDAProjectConfig::config_info;
QDAProjectConfig::JsonType QDAProjectConfig::config_json_type;

QDAProjectConfig::QDAProjectConfig(QObject *parent) :
    QObject(parent)
{
    
}

QDAProjectConfig::~QDAProjectConfig()
{

}

QByteArray QDAProjectConfig::LoadJsonConfig(const QString& file_name)
{
    QByteArray json_data;
    QCKFile::State ret = QCKFile::LoadFile(file_name, json_data);
    if (config_json_type == JsonType::Create) {
        QFileInfo info(file_name);
        config_info.proj_dir = info.dir().absolutePath();
        qDebug() << "config file dir" << config_info.proj_dir;
    } else if (config_json_type == JsonType::Open) {
        config_info.proj_dir = file_name.mid(0, file_name.size()-strlen(PROJECT_CONF_JSON));
    }
    if (ret == QCKFile::State::Succeed) {
        return json_data;
    }
    return QByteArray();
}

// proj_name + dir_proj + dir_codes + dir_help
bool QDAProjectConfig::JsonToConfig(const QString &json_str, QDAProjectConfig::ConfigInfo &config)
{
    // check json data
    QJsonDocument json_doc = QJsonDocument::fromJson(json_str.toUtf8());
    if (json_doc.isEmpty() || !json_doc.isObject()) {
        QMessageBox::critical(NULL, __FUNCTION__, "Error json config ! Or Config is not an json object!");
        return false;
    }
    
    // parse json key-values
    QJsonObject json_obj = json_doc.object();
    if (json_obj.contains("proj_name")) {
        config.proj_name = json_obj["proj_name"].toString();
    }
    
    if (json_obj.contains("dir_proj")) {
        config.proj_dir = json_obj["dir_proj"].toString();
    }

    if (json_obj.contains("options")) {
        QJsonObject options = json_obj["options"].toObject();
        QStringList key = options.keys();
        for (size_t idx = 0; idx < key.size(); idx++)
        {
            config.options[key[idx]] = options[key[idx]].toString();
        }
    }
    
    // parse group list
    if (json_obj.contains("dir_codes")) {
        QJsonArray group_arr = json_obj["dir_codes"].toArray();
        for (int idx=0; idx<group_arr.size(); idx++) {
            QJsonObject obj = group_arr[idx].toObject();
            // group + group_dir + modules
            QDAProjectConfig::Group group_ = QDAProjectConfig::JsonToGroup(obj);
            config.groups.emplace_back(group_);
        }
    }
    
    // parse dir_help
    if (json_obj.contains("dir_help")) {
        QJsonObject obj = json_obj["dir_help"].toObject();
        QStringList keys = obj.keys();
        for(int idx=0; idx<keys.size(); idx++) {
            config.dir_help[keys[idx]] = obj[keys[idx]].toString();
        }
    }
        
    return true;
}

// group(type) + group_dir + modules
QDAProjectConfig::Group QDAProjectConfig::JsonToGroup(const QJsonObject &obj)
{
    QDAProjectConfig::Group group_;
    if (obj.contains("group")) {
        group_.type = obj["group"].toString();
    }
    
    if (obj.contains("group_dir")) {
        group_.group_dir = obj["group_dir"].toString();
    }
    
    if (obj.contains("modules")) {
        // name + option + gen_lib + deps
        QJsonArray module_arr = obj["modules"].toArray();
        for (int idx_m=0; idx_m<module_arr.size(); idx_m++) {
            QJsonObject obj = module_arr[idx_m].toObject();
            QDAProjectConfig::Module module_ = QDAProjectConfig::JsonToModule(obj);
            group_.modules.emplace_back(module_);
        }
    }
    return group_;
}

// module(name) + option + gen_lib + deps
QDAProjectConfig::Module QDAProjectConfig::JsonToModule(const QJsonObject &obj)
{
    QDAProjectConfig::Module module_;
    if (obj.contains("module")) {
        module_.name = obj["module"].toString();
    }
    
    if (obj.contains("option")) {
        module_.option = obj["option"].toString();
    }
    
    if (obj.contains("gen_lib")) {
        module_.gen_lib = obj["gen_lib"].toString();
    }
    
    if (obj.contains("deps")) {
        QJsonArray deps_arr = obj["deps"].toArray();
        for (int idx=0; idx<deps_arr.size(); idx++) {
            QString deps = deps_arr[idx].toString();
            module_.deps.emplace_back(deps);
        }
    }
    return module_;
}

QString QDAProjectConfig::JsonStringFromConfig(const QDAProjectConfig::ConfigInfo &config)
{
    QJsonObject json_obj = JsonFromConfig(config);
    QString json_str = QString(QJsonDocument(json_obj).toJson());
    return json_str;
}

// proj_name + dir_proj + dir_codes + dir_help
QJsonObject QDAProjectConfig::JsonFromConfig(const QDAProjectConfig::ConfigInfo &config)
{
    QJsonObject json_obj;
    json_obj.insert("proj_name", config.proj_name);
    json_obj.insert("dir_proj", config.proj_dir);

    QJsonObject options_obj;
    for (auto iter = config.options.begin(); iter != config.options.end(); iter++) {
        options_obj.insert(iter->first, iter->second);
    }
    json_obj.insert("options", options_obj);

    QJsonArray group_arr;
    for (int idx=0; idx<config.groups.size(); idx++) {
        QJsonObject group = QDAProjectConfig::JsonFromGroup(config.groups[idx]);
        group_arr.append(group);
    }
    json_obj.insert("dir_codes", group_arr);

    // parse dir_help
    QJsonObject obj;
    for (auto iter=config.dir_help.begin(); iter!=config.dir_help.end(); iter++) {
        obj.insert(iter->first, iter->second);
    }
    json_obj.insert("dir_help", obj);
    
    return json_obj;
}

// group(type) + group_dir + modules
QJsonObject QDAProjectConfig::JsonFromGroup(const QDAProjectConfig::Group &group_) {
    QJsonObject obj;
    obj.insert("group", group_.type);
    obj.insert("group_dir", group_.group_dir);
    
    QJsonArray module_arr;
    for (int idx=0; idx<group_.modules.size(); idx++) {
        QJsonObject item = QDAProjectConfig::JsonFromModule(group_.modules[idx]);
        module_arr.append(item);
    }
    obj.insert("modules", module_arr);
    return obj;
}

// module(name) + option + gen_lib + deps
QJsonObject QDAProjectConfig::JsonFromModule(const QDAProjectConfig::Module &module_) {
    QJsonObject obj;
    obj.insert("module", module_.name);
    obj.insert("option", module_.option);
    obj.insert("gen_lib", module_.gen_lib);

    QJsonArray deps_arr;
    for (int idx=0; idx<module_.deps.size(); idx++) {
        deps_arr.append(module_.deps[idx]);
    }
    obj.insert("deps", deps_arr);
    return obj;
}

bool QDAProjectConfig::FixProjDir(QDAProjectConfig::ConfigInfo &config)
{
    if (config_json_type == JsonType::Create) {
        // not absolute path
        if (config.proj_dir.startsWith("./")) {
            config.proj_dir = config_info.proj_dir + config.proj_dir.mid(1);
        } 
        else if (config.proj_dir.startsWith("../"))
        {
			config.proj_dir = config_info.proj_dir + "/" + config.proj_dir;
        }
		QDir dir(config.proj_dir);
        config.proj_dir = dir.absolutePath();
    }
    else if (config_json_type == JsonType::Open) 
    {
        if (config.proj_dir != config_info.proj_dir) {
            config.proj_dir = config_info.proj_dir;
        }
    }
    qDebug() << "Project root dir : " << config_info.proj_dir;
    return true;
}

bool QDAProjectConfig::AddConfigByString(const QString &json_str)
{
    // parse json_str to config
    QDAProjectConfig::ConfigInfo config;
    bool ret = JsonToConfig(json_str, config);
    if (ret) {
        // Fix Path
        ret = FixProjDir(config);
        if (!ret) {
            return false;
        }
        config.json_file = config.proj_dir + PROJECT_CONF_JSON;
        AddConfig(std::move(config));
        return true;
    }
    return false;
}

void QDAProjectConfig::AddConfig(QDAProjectConfig::ConfigInfo &&cfg)
{
    config_info.clear();
    config_info = cfg;
}

QDAProjectConfig::ConfigInfo QDAProjectConfig::GetConfig()
{
    if (config_info.proj_dir != "") {
        return config_info;
    }
    
    QMessageBox::warning(NULL, "Project Config", "Invalid json config !");
    return QDAProjectConfig::ConfigInfo();
}
