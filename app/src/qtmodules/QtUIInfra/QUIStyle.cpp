// MIT License
//
// Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)
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

#include "QUIStyle.h"

#include <QMainWindow>
#include <QDockWidget>
#include <QListView>
#include <QListWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QStyleFactory>

NS_QUI_BEGIN
void Style::SetMainWindow(QMainWindow* window)
{
	if (!window) {
		return;
	}

	window->setStyleSheet("QMainWindow { background-color: rgb(49, 53, 64); }");
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

void Style::SetListView(QListView* view)
{
	if (!view) {
		return;
	}

	view->setStyleSheet("\
						QListView::item { font: 14px; color: white; height: 50px;} \
                        QListView::item:hover{ color:gray; } \
						QListView::item::selected, QListView::branch::selected { background-color: blue; } \
						QListView { background-color: rgb(49, 53, 64); } \
						");
}

void Style::SetListWidget(QListWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setStyleSheet("\
						QListView::item { font: 14px; color: white; height: 50px; border:1px solid #797979; } \
                        QListView::item:hover{ color:gray; } \
						QListView::item::selected, QListView::branch::selected { background-color: blue; } \
						QListView { background-color: rgb(49, 53, 64); } \
						");

}

void Style::SetTreeWidget(QTreeWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setStyle(QStyleFactory::create("windows"));
	//widget->setStyleSheet("QTreeWidget::item{ height: 50px; background-color: rgb(49, 53, 64); }");
	widget->setStyleSheet("\
						QHeaderView::section { font: 20px; color:#CCCCCC; height: 50px; background-color: rgb(49, 53, 64);} \
						QTreeView { background-color: rgb(49, 53, 64); } \
						QTreeView::item { font: 14px; color:#CCCCCC; height: 50px; } \
                        QTreeView::item:hover{ color:white; } \
						QTreeView::item::selected, QTreeView::branch::selected { color:#17A387; border:1px solid #797979; } \
						");
}

void Style::SetPushButton(QPushButton* btn)
{
	if (!btn) {
		return;
	}

	btn->setStyleSheet("\
                        QPushButton{ border-radius:6px; background-color: white; width:150px; height:44px;} \
                        QPushButton::hover{ color:white; background-color: #17A387; } \
                        ");
}

NS_QUI_END