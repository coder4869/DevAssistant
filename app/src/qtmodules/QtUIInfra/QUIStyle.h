// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#pragma once

#include <CUtils/def_build.h>
#include <CUtils/def_macro.h>
#include "QtUIInfraDef.h"

class QMainWindow;
class QDockWidget;
class QListView;
class QListWidget;
class QTreeWidget;
class QPushButton;

NS_QUI_BEGIN

//class QUI_CLASS Style
//{
//public:
namespace Style {
	void SetMainWindow(QMainWindow* window);

	void SetDockWidget(QDockWidget* widget);

	void SetListView(QListView* view);

	void SetListWidget(QListWidget* widget);

	void SetTreeWidget(QTreeWidget* widget);

	void SetPushButton(QPushButton* btn);
};
NS_QUI_END


