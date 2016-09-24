// Copyright (c) 2015-2016 Hypha
#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QtWidgets/QWidget>
#include "../main/instance.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget {
  Q_OBJECT

 public:
  explicit UserWindow(Instance *instance, QWidget *parent = 0);
  ~UserWindow();

 public slots:
  void reload();
  void loadOnline();
  bool isOnline(QString username);
  void reloadUserStatus(QString username);
  QString lastConnection(QString username);

 private:
  Ui::UserWindow *ui;

 protected:
  Instance *instance;
 private slots:
  void on_newUserButton_clicked();
  void on_listWidget_currentTextChanged(const QString &currentText);
  void on_firstnameEdit_editingFinished();
  void on_lastnameEdit_editingFinished();
  void on_mailEdit_editingFinished();
  void on_deviceIdEdit_editingFinished();
  void on_saveButton_clicked();
};

#endif  // USERWINDOW_H
