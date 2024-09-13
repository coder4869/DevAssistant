// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#ifndef QCK_JSON_H
#define QCK_JSON_H

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>

class QString;
class QJsonObject;
class QJsonArray;
class QJsonDocument;

class QCKJson
{
public:
	static bool LoadJsonObjectFromFile(const QString& json_file, QJsonObject& json_obj);
	static bool LoadJsonArrayFromFile(const QString& json_file, QJsonArray & json_arr);
	static bool GetJsonDocFromFile(const QString& json_file, QJsonDocument& json_doc);
};

#endif /* QCK_JSON_H */
