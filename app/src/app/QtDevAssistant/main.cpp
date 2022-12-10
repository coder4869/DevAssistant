#include <QApplication>
#include <QCoreApplication>

#include "QDAMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("DevAssistant");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    QDAMainWindow window;
    window.setWindowTitle("DevAssistant");
    window.showMaximized();
    window.show();
    
    return app.exec();
}
