// Copyright (c) 2015-2016 Hypha
#ifndef NEWCONFIGWIZZARD_H
#define NEWCONFIGWIZZARD_H

#include <QDialog>

namespace Ui {
class NewConfigWizzard;
}

class NewConfigWizzard : public QDialog {
  Q_OBJECT

 public:
  explicit NewConfigWizzard(QWidget *parent = 0);
  ~NewConfigWizzard();

 private slots:
  void on_selectFileButton_clicked();

  void on_selectDBButton_clicked();

  void on_selectUserDBButton_clicked();

  void on_cancelButton_clicked();

  void on_nextButton_clicked();

 private:
  Ui::NewConfigWizzard *ui;
};

#endif  // NEWCONFIGWIZZARD_H
