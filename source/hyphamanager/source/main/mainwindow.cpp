// Copyright (c) 2015-2017 Hypha
#include "main/mainwindow.h"
#include <hyphamanager/core/aboutdialog.h>
#include <QtCore/QThread>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "hyphamanager/settings/settingswindow.h"
#include "hyphamanager/settings/translation.h"
#include "hyphamanager/wizzards/newconfigwizzard.h"
#include "main/splashscreen.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  instance = 0;
  SplashScreen splash(this);
  splash.show();
  splash.setMessage("Starting");
  ui->setupUi(this);
  createLanguageMenu();
  QThread::msleep(1000);
  splash.finish(this);
}

MainWindow::~MainWindow() {
  if (this->instance) {
    if (this->connectionWindow) {
      this->connectionWindow->savePositions();
      this->connectionWindow->saveConfig();

      delete connectionWindow;
    }
    delete instance;
  }
  delete ui;
}

void MainWindow::on_actionAbout_Hypha_Client_triggered() {
  AboutDialog dialog(this);
  dialog.exec();
}

void MainWindow::createLanguageMenu() {
  QStringList languages = Translation::instance()->getLanguages();
  foreach (QString language, languages) {
    QAction *action = new QAction(language, this);
    // Set current language as checked.
    connect(action, SIGNAL(triggered()), this, SLOT(onLanguageChosen()));
    action->setCheckable(true);
    if (language == Translation::instance()->language()) {
      action->setChecked(true);
    }
    ui->menuLanguage->addAction(action);
  }
}

void MainWindow::onLanguageChosen() {
  QAction *action = qobject_cast<QAction *>(sender());
  // set all actions as not checked
  foreach (QAction *lang, ui->menuLanguage->actions()) {
    lang->setChecked(false);
  }
  // Set currently selected action as checked.
  action->setChecked(true);
  Translation::instance()->setLanguage(action->text());
  QMessageBox::information(
      this, "Restart",
      "You have to restart the program to make changes effect.");
}

void MainWindow::on_actionOpen_triggered() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Hypha Config"), "", tr("Hypha Config (*.xml)"));
  if (fileName.isEmpty()) return;
  instance = new Instance(fileName, this);
  userWindow = new UserWindow(instance, this);
  connectionWindow = new ConnectionWindow(instance, this);
  ui->tabWidget->insertTab(
      0, userWindow, QIcon(":/actions/images/actions/users.svg"), "Users");
  ui->tabWidget->insertTab(1, connectionWindow,
                           QIcon(":/actions/images/actions/connections.svg"),
                           "Designer");
}

void MainWindow::on_actionSettings_triggered() {
  if (instance) {
    SettingsWindow settingsWindow(this->instance->getClientSettings(), this);
    settingsWindow.exec();
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {}

void MainWindow::on_actionNew_triggered() {
  NewConfigWizzard newConfigWizzard(this);
  newConfigWizzard.exec();
}
