#include <hypha/database/database.h>
#include "rulesadddialog.h"
#include "ui_rulesadddialog.h"

RulesAddDialog::RulesAddDialog(QString username, QDate date, hypha::database::Database *database, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::RulesAddDialog) {
  this->username = username;
  this->date = date;
  this->database = database;
  ui->setupUi(this);
  init();
}

RulesAddDialog::~RulesAddDialog() {
  delete ui;
  delete rulesItem;
}

void RulesAddDialog::init() {
  this->rulesItem = new RulesItem(username, QDateTime(date), QDateTime(date), hypha::blechuhr::RTYPE::WORKING, database);
  ui->center->addWidget(rulesItem);
}

void RulesAddDialog::on_buttonBox_accepted() {
  rulesItem->save();
}
