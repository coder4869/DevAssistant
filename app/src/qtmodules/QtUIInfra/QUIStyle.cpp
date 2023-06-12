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
#include <QStyleFactory>

void QUIStyle::SetMainWindow(QMainWindow* window)
{
	if (!window) {
		return;
	}

	window->setStyleSheet("QMainWindow { background-color: rgb(49, 53, 64); }");
}

void QUIStyle::SetDockWidget(QDockWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setWindowFlag(Qt::FramelessWindowHint);
	widget->setFeatures(QDockWidget::NoDockWidgetFeatures);
	widget->setStyleSheet("QDockWidget { background-color: rgb(49, 53, 64); }");
}

void QUIStyle::SetListView(QListView* view)
{
	if (!view) {
		return;
	}

	view->setStyleSheet("\
						QListView::item { font: 14px; color: white; height: 55px;} \
						QListView::item::selected, QListView::branch::selected { background-color: blue; } \
						QListView { background-color: rgb(49, 53, 64); } \
						");
}

void QUIStyle::SetListWidget(QListWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setStyleSheet("\
						QListView::item { font: 14px; color: white; height: 55px;} \
						QListView::item::selected, QListView::branch::selected { background-color: blue; } \
						QListView { background-color: rgb(49, 53, 64); } \
						");

}

void QUIStyle::SetTreeWidget(QTreeWidget* widget)
{
	if (!widget) {
		return;
	}

	widget->setStyle(QStyleFactory::create("windows"));
	//widget->setStyleSheet("QTreeWidget::item{ height: 55px; background-color: rgb(49, 53, 64); }");
	widget->setStyleSheet("\
						QHeaderView::section { font: 20px; color: white; height: 55px; background-color: rgb(49, 53, 64);} \
						QTreeView::item { font: 14px; color: white; height: 55px; } \
						QTreeView::item::selected, QTreeView::branch::selected { background-color: blue; } \
						QTreeView { background-color: rgb(49, 53, 64); } \
						");
}