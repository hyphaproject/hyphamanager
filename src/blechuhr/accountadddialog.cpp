#include <hypha/database/database.h>
#include "accountadddialog.h"
#include "ui_accountadddialog.h"
#include "model/type.h"

AccountAddDialog::AccountAddDialog(QString username, QDate date, hypha::database::Database *database, QWidget *parent):
    QDialog(parent),
    ui(new Ui::AccountAddDialog) {
    this->username = username;
    this->date = date;
    this->database = database;
    ui->setupUi(this);
    init();
}

AccountAddDialog::~AccountAddDialog() {
    delete ui;
    delete accountItem;
}

void AccountAddDialog::init() {
    this->accountItem = new AccountItem(username, QDateTime(date), QDateTime(date), hypha::blechuhr::TYPE::WORKING, 0, "", database);
    ui->center->addWidget(accountItem);
}

void AccountAddDialog::on_buttonBox_accepted() {
    accountItem->save();
}
