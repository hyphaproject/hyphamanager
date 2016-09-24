// Copyright (c) 2015-2016 Hypha
#include "user/userwindow.h"
#include <Poco/Data/RecordSet.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <QtCore/QDateTime>
#include <QtCore/QTimeZone>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QMessageBox>
#include "ui_userwindow.h"

UserWindow::UserWindow(Instance *instance, QWidget *parent)
    : QWidget(parent), ui(new Ui::UserWindow) {
  ui->setupUi(this);
  this->instance = instance;
  reload();
}

UserWindow::~UserWindow() { delete ui; }

void UserWindow::reload() {
  ui->listWidget->clear();
  for (std::string user : instance->getUserDatabase()->getUsers()) {
    ui->listWidget->addItem(QString::fromStdString(user));
  }
  loadOnline();
}

void UserWindow::loadOnline() {
  for (int i = 0; i < ui->listWidget->count(); ++i) {
    QListWidgetItem *item = ui->listWidget->item(i);
    if (isOnline(item->text())) {
      item->setIcon(QIcon(":/users/images/actions/online.svg"));
      item->setToolTip("present since: " + this->lastConnection(item->text()));
    }
  }
}

bool UserWindow::isOnline(QString username) {
  std::list<std::string> devices =
      instance->getUserDatabase()->getDevices(username.toStdString());
  // number of registrations today
  int connections = 0;
  for (std::string device : devices) {
    Poco::Data::Statement statement = instance->getDatabase()->getStatement();
    statement << "select count(`id`) from `deviceonline` where `deviceid`='" +
                     device + "' and date(`time`) = '" +
                     QDateTime::currentDateTimeUtc()
                         .date()
                         .toString("yyyy-MM-dd")
                         .toStdString() +
                     "';";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
      connections += rs[0].convert<int>();
      more = rs.moveNext();
    }
  }
  return connections % 2 == 1;
}

void UserWindow::reloadUserStatus(QString username) {
  std::list<std::string> devices =
      instance->getUserDatabase()->getDevices(username.toStdString());
  QDateTime datetime;
  for (std::string device : devices) {
    Poco::Data::Statement statement = instance->getDatabase()->getStatement();
    statement << "select `time` from `deviceonline` where `deviceid`='" +
                     device + "' ORDER BY `time` desc;";
    try {
      statement.execute();
    } catch (Poco::NotFoundException &e) {
      continue;
    }

    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
      std::string dateTimeStr = rs[0].convert<std::string>();
      QDateTime dt = QDateTime::fromString(QString::fromStdString(dateTimeStr));
      dt.setTimeSpec(Qt::UTC);
      if (dt > datetime) {
        ui->deviceOnlineLabel->setText(QString::fromStdString(device));
        ui->dateTimeEdit->setDateTime(dt.toLocalTime());
        datetime = dt;
      }
      more = rs.moveNext();
      break;
    }
  }
}

QString UserWindow::lastConnection(QString username) {
  std::list<std::string> devices =
      instance->getUserDatabase()->getDevices(username.toStdString());
  QDateTime datetime;
  for (std::string device : devices) {
    Poco::Data::Statement statement = instance->getDatabase()->getStatement();
    statement << "select time from deviceonline where deviceid='" + device +
                     "' ORDER BY time desc";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
      std::string dateTimeStr = rs[0].convert<std::string>();
      QDateTime dt = QDateTime::fromString(QString::fromStdString(dateTimeStr));
      dt.setTimeSpec(Qt::UTC);
      if (dt > datetime) {
        datetime = dt;
      }
      more = rs.moveNext();
      break;
    }
  }
  return datetime.toLocalTime().toString("hh:mm");
}

void UserWindow::on_newUserButton_clicked() {
  QString username = QInputDialog::getText(this, "New User", "Username");
  if (instance->getUserDatabase()->createUser(username.toStdString(), "Unknown",
                                              "Unknown", "")) {
    reload();
  } else {
    QMessageBox::warning(this, "Error",
                         "The user could not been added to the database.");
  }
}

void UserWindow::on_listWidget_currentTextChanged(const QString &currentText) {
  ui->groupBox->setTitle(currentText);
  ui->firstnameEdit->setText(QString::fromStdString(
      instance->getUserDatabase()->getFirstname(currentText.toStdString())));
  ui->lastnameEdit->setText(QString::fromStdString(
      instance->getUserDatabase()->getLastname(currentText.toStdString())));
  ui->mailEdit->setText(QString::fromStdString(
      instance->getUserDatabase()->getMail(currentText.toStdString())));
  std::list<std::string> devs =
      instance->getUserDatabase()->getDevices(currentText.toStdString());
  std::ostringstream oss;
  std::list<std::string>::const_iterator iter = devs.begin();
  while (iter != devs.end()) {
    oss << *iter;
    iter++;
    if (iter != devs.end()) oss << ", ";
  }
  std::string deviceids = oss.str();
  ui->deviceIdEdit->setText(QString::fromStdString(deviceids));
  ui->saveButton->setEnabled(false);
  reloadUserStatus(currentText);
}

void UserWindow::on_firstnameEdit_editingFinished() {
  ui->saveButton->setEnabled(true);
}

void UserWindow::on_lastnameEdit_editingFinished() {
  ui->saveButton->setEnabled(true);
}

void UserWindow::on_mailEdit_editingFinished() {
  ui->saveButton->setEnabled(true);
}

void UserWindow::on_deviceIdEdit_editingFinished() {
  ui->saveButton->setEnabled(true);
}

void UserWindow::on_saveButton_clicked() {
  if (instance->getUserDatabase()->updateUser(
          ui->groupBox->title().toStdString(),
          ui->firstnameEdit->text().toStdString(),
          ui->lastnameEdit->text().toStdString(),
          ui->mailEdit->text().toStdString(),
          ui->deviceIdEdit->text().toStdString()))
    ui->saveButton->setEnabled(false);
}
