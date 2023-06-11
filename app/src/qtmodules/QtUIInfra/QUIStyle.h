#pragma once

class QMainWindow;
class QDockWidget;
class QListView;
class QListWidget;
class QTreeWidget;

class QUIStyle
{
public:
	static void SetMainWindow(QMainWindow* window);

	static void SetDockWidget(QDockWidget *widget);

	static void SetListView(QListView* view);
	
	static void SetListWidget(QListWidget* widget);
	
	static void SetTreeWidget(QTreeWidget* widget);
};

