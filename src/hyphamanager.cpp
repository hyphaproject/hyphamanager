#include <QtWidgets/QApplication>
#include "main/mainwindow.h"
#include "settings/translation.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setOrganizationDomain("hypha");
    a.setOrganizationName("hypha");
    a.setApplicationName("hyphamanager");
    // translation
    Translation::instance();

    MainWindow w;
    w.show();

    return a.exec();
}
