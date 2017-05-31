// Copyright (c) 2015-2016 Hypha
#include <hyphamanager/settings/translation.h>
#include <QtWidgets/QApplication>
#include "main/mainwindow.h"

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
