// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QDA_PROJECT_CONFIG_H
#define QDA_PROJECT_CONFIG_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

#include <QObject>

class QByteArray;
class QJsonObject;

extern const char* PROJECT_CONF_JSON;

class QDAProjectConfig : public QObject
{
    Q_OBJECT
    
public:
    enum class JsonType {
        Create,
        Open
    };
    
    struct Module {
        QString name = "";
        QString option = "";
        QString gen_lib = "";
        std::vector<QString> deps;
    };
    
    struct Group {
        QString type = "";
        QString group_dir = "";
        std::vector<Module> modules;
    };
    
    struct ConfigInfo {
        QString json_file = "";
        QString proj_name = "";
        QString proj_dir = "";
        std::map<QString, QString> options;
        std::map<QString, QString> dir_help;
        std::vector<Group> groups;

        void clear() {
            groups.clear();
            options.clear();
            dir_help.clear();
        }
    };
    
public:
    explicit QDAProjectConfig(QObject *parent = nullptr);
    virtual ~QDAProjectConfig();
    
    static QByteArray LoadJsonConfig(const QString& file_name);
    // proj_name + dir_proj + dir_codes + dir_help
    static bool JsonToConfig(const QString &json_str, QDAProjectConfig::ConfigInfo &config);
    // proj_name + dir_proj + dir_codes + dir_help
    static QJsonObject JsonFromConfig(const QDAProjectConfig::ConfigInfo &config);
    static QString JsonStringFromConfig(const QDAProjectConfig::ConfigInfo &config);
    
    static bool FixProjDir(QDAProjectConfig::ConfigInfo &config);
    
    static bool AddConfigByString(const QString &json_str);
    static void AddConfig(ConfigInfo &&cfg);
    static QDAProjectConfig::ConfigInfo GetConfig();
    
    static JsonType config_json_type;
    
private:
    // group(type) + group_dir + modules
    static Group JsonToGroup(const QJsonObject &obj);
    // module(name) + option + gen_lib + deps
    static Module JsonToModule(const QJsonObject &obj);
    // group(type) + group_dir + modules
    static QJsonObject JsonFromGroup(const Group &group_);
    // module(name) + option + gen_lib + deps
    static QJsonObject JsonFromModule(const Module &module_);
    
private:
    static QMap<JsonType, QString> json_config_files;
    static ConfigInfo config_info;
};

#endif // QDA_PROJECT_CONFIG_H
