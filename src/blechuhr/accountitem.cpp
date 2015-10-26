#include <hypha/database/database.h>
#include "accountitem.h"
#include "ui_accountitem.h"
#include "model/type.h"

AccountItem::AccountItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountItem) {
    ui->setupUi(this);
    initType();
    init();
}

AccountItem::AccountItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::TYPE type, float amount, QString name, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem) {
    ui->setupUi(this);
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->amount = amount;
    this->name = name;
    this->database = database;
    this->isIterative = false;
    initType();
    init();
}

AccountItem::AccountItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::TYPE type, float amount, QString name, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem) {
    ui->setupUi(this);
    ui->iterativeCheckBox->hide();
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->amount = amount;
    this->name = name;
    this->database = database;
    this->isIterative = false;
    initType();
    init();
}

AccountItem::AccountItem(QString username, QDateTime start, QDateTime end, hypha::blechuhr::ITYPE type, QTime starttime, QTime endtime, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem) {
    ui->setupUi(this);
    this->username = username;
    this->start = start;
    this->end = end;
    this->itype = type;
    this->database = database;
    this->isIterative = true;
    this->starttime = starttime;
    this->endtime = endtime;
    initType();
    init();
}

AccountItem::AccountItem(QString id, QString username, QDateTime start, QDateTime end, hypha::blechuhr::ITYPE type, QTime starttime, QTime endtime, hypha::database::Database *database, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AccountItem) {
    ui->setupUi(this);
    ui->iterativeCheckBox->hide();
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->itype = type;
    this->database = database;
    this->isIterative = true;
    this->starttime = starttime;
    this->endtime = endtime;
    initType();
    init();
}

AccountItem::~AccountItem() {
    delete ui;
}

void AccountItem::save() {
    Poco::Data::Statement statement = database->getStatement();

    if (isIterative) {
        if (id.isEmpty()) {
            statement << "insert into iterativeaccount(username, type, start, end, starttime, endtime) values(?, ?, ?, ?, ?, ?);",
                      Poco::Data::use(username.toStdString()), Poco::Data::use(ui->typeComboBox->currentText().toStdString()),
                      Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->startTimeEdit->time().toString().toStdString()),
                      Poco::Data::use(ui->endTimeEdit->time().toString().toStdString());
        } else {
            statement << "update iterativeaccount set username=?, type=?, start=?, end=?, starttime=?, endtime=? where id = ?;",
                      Poco::Data::use(username.toStdString()), Poco::Data::use(ui->typeComboBox->currentText().toStdString()),
                      Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->startTimeEdit->time().toString().toStdString()),
                      Poco::Data::use(ui->endTimeEdit->time().toString().toStdString()),
                      Poco::Data::use(id.toStdString());
        }
    } else {
        if (id.isEmpty()) {
            statement << "insert into account(username, type, start, end, amount, name) values(?, ?, ?, ?, ?, ?);",
                      Poco::Data::use(username.toStdString()), Poco::Data::use(ui->typeComboBox->currentText().toStdString()),
                      Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->amountSpinBox->value()),
                      Poco::Data::use(ui->nameLineEdit->text().toStdString());
        } else {
            statement << "update account set username=?, type=?, start=?, end=?, amount=?, name=? where id = ?;",
                      Poco::Data::use(username.toStdString()), Poco::Data::use(ui->typeComboBox->currentText().toStdString()),
                      Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                      Poco::Data::use(ui->amountSpinBox->value()),
                      Poco::Data::use(ui->nameLineEdit->text().toStdString()),
                      Poco::Data::use(this->id.toStdString());
        }
    }
    statement.execute();
}

void AccountItem::deleteFromDatabase() {
    Poco::Data::Statement statement = database->getStatement();
    if (id.isEmpty()) {
    } else {
        if (isIterative) {
            statement << "delete from iterativeaccount where id = ?;",
                      Poco::Data::use(this->id.toStdString());
        } else {
            statement << "delete from account where id = ?;",
                      Poco::Data::use(this->id.toStdString());
        }
        statement.execute();
    }
}

void AccountItem::init() {
    ui->startDateTimeEdit->setDateTime(start.toLocalTime());
    ui->endDateTimeEdit->setDateTime(end.toLocalTime());
    if (isIterative) {
        ui->typeComboBox->setCurrentText(QString::fromStdString(hypha::blechuhr::ITypeToString(itype)));
        ui->startTimeEdit->setTime(this->starttime);
        ui->endTimeEdit->setTime(this->endtime);
    } else {
        ui->typeComboBox->setCurrentText(QString::fromStdString(hypha::blechuhr::TypeToString(type)));
        ui->nameLineEdit->setText(name);
        ui->amountSpinBox->setValue(amount);
    }
    updateElements();

}

void AccountItem::initType() {
    ui->typeComboBox->clear();
    int i = 0;
    if (isIterative) {
        for (const auto &t : hypha::blechuhr::ITYPE()) {
            QString type = QString::fromStdString(hypha::blechuhr::ITypeToString(t));
            ui->typeComboBox->addItem(type);
            ui->typeComboBox->setItemText(i, type);
            ui->typeComboBox->setItemIcon(i, QIcon(":/blechuhr/" + type));
            i++;
        }
    } else {
        for (const auto &t : hypha::blechuhr::TYPE()) {
            QString type = QString::fromStdString(hypha::blechuhr::TypeToString(t));
            ui->typeComboBox->addItem(type);
            ui->typeComboBox->setItemText(i, type);
            ui->typeComboBox->setItemIcon(i, QIcon(":/blechuhr/" + type));
            i++;
        }
    }
}

void AccountItem::on_iterativeCheckBox_clicked(bool checked) {
    isIterative = checked;
    updateElements();
}

void AccountItem::updateElements() {
    if (isIterative) {
        ui->amountSpinBox->hide();
        ui->nameLineEdit->hide();
        ui->startTimeEdit->show();
        ui->endTimeEdit->show();
    } else {
        ui->amountSpinBox->show();
        ui->nameLineEdit->show();
        ui->startTimeEdit->hide();
        ui->endTimeEdit->hide();
    }
    initType();
    ui->horizontalLayout->addStretch();
}
