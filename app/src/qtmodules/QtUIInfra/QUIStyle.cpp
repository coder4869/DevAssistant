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