// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QCKJson.h"

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>

#include "QCKFile.h"

bool QCKJson::LoadJsonObjectFromFile(const QString& json_file, QJsonObject& json_obj)
{
	QJsonDocument json_doc;
	if (!GetJsonDocFromFile(json_file, json_doc) || !json_doc.isObject()) {
		QMessageBox::critical(NULL, __FUNCTION__, json_file + " is not JsonObject!");
		return false;
	}

	json_obj = json_doc.object();
	return true;
}

bool QCKJson::LoadJsonArrayFromFile(const QString& json_file, QJsonArray& json_arr)
{
	QJsonDocument json_doc;
	if (!GetJsonDocFromFile(json_file, json_doc) || !json_doc.isArray()) {
		QMessageBox::critical(NULL, __FUNCTION__, json_file + " is not JsonArray!");
		return false;
	}

	json_arr = json_doc.array();
	return true;
}

bool QCKJson::GetJsonDocFromFile(const QString& json_file, QJsonDocument& json_doc)
{
	// Load File
	QByteArray file_data;
	if (QCKFile::LoadFile(json_file, file_data) != QCKFile::State::Succeed) {
		QMessageBox::critical(NULL, __FUNCTION__, json_file + " Not Exist!");
		return false;
	}

	QString json_str = file_data;
	json_doc = QJsonDocument::fromJson(json_str.toUtf8());
	if (json_doc.isEmpty()) {
		QMessageBox::critical(NULL, __FUNCTION__, json_file + " parse json failed!");
		return false;
	}

	return true;
}
