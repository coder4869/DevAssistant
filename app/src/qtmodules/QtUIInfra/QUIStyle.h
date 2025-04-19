// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>
#include "QtUIInfraDef.h"

class QDockWidget;
class QTreeWidget;
class QString;

NS_QUI_BEGIN

//class QUI_CLASS Style
//{
//public:
namespace Style {
	QString MainWindowStyle();

	void SetDockWidget(QDockWidget* widget);

	void SetTreeWidget(QTreeWidget* widget);

	QString ListView();

	QString ListWidget();

	QString PushButton();
	QString PushButtonCyan();

};
NS_QUI_END


