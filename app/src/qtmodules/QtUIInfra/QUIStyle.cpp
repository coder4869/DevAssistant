// Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

#include "QUIStyle.h"

#include <QDockWidget>
#include <QTreeWidget>
#include <QStyleFactory>

NS_QUI_BEGIN
QString Style::MainWindowStyle()
{
	return R"(
		QMainWindow { background-color: rgb(49, 53, 64); }
	)";
}

void Style::SetDockWidget(QDockWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setWindowFlag(Qt::FramelessWindowHint);
	widget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	widget->setStyleSheet("QDockWidget { background-color: rgb(49, 53, 64); }");
}

void Style::SetTreeWidget(QTreeWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setStyle(QStyleFactory::create("windows"));
	//widget->setStyleSheet("QTreeWidget::item{ height: 50px; background-color: rgb(49, 53, 64); }");
	widget->setStyleSheet(R"(
		QHeaderView::section { font: 20px; color:#CCCCCC; height: 50px; background-color: rgb(49, 53, 64);}
		QTreeView { background-color: rgb(49, 53, 64); }
		QTreeView::item { font: 14px; color:#CCCCCC; height: 50px; }
        QTreeView::item:hover{ color:white; }
		QTreeView::item::selected, QTreeView::branch::selected { color:#17A387; border:1px solid #797979; }
	)");
}

QString Style::ListView()
{
	return R"(
		QListView::item { font: 14px; color: white; height: 50px;}
        QListView::item:hover{ color:gray; }
		QListView::item::selected, QListView::branch::selected { background-color: blue; }
		QListView { background-color: rgb(49, 53, 64); }
	)";
}

QString Style::ListWidget()
{
	return R"(
		QListView::item { font: 14px; color: white; height: 50px; border:1px solid #797979; }
        QListView::item:hover{ color:gray; }
		QListView::item::selected, QListView::branch::selected { background-color: blue; }
		QListView { background-color: rgb(49, 53, 64); }
	)";
}

QString Style::PushButton()
{
	return R"(
        QPushButton{ border-radius:6px; background-color: white; width:150px; height:44px;}
        QPushButton::hover{ color:white; background-color: #17A387; }
    )";
}

QString Style::PushButtonCyan()
{
	return R"(
        QPushButton {
            border: 1px solid gray;
            border-radius: 5px;
            background-color: rgb(0, 159, 170); 
            padding:8px; 
            color:rgb(255, 255, 255);
        }
 
        QPushButton:hover {
            border: 1px solid #005566;
            background-color: rgb(0, 191, 203); 
        }
 
        QPushButton:pressed {
            border: 1px solid #00333F;
            background-color: rgb(0, 119, 130); 
            padding-top: 9px;
            padding-bottom: 7px; 
        }
    )";
}

NS_QUI_END