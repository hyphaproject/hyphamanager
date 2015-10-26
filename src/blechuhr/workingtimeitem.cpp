#include <hypha/database/database.h>
#include "workingtimeitem.h"
#include "ui_workingtimeitem.h"

WorkingTimeItem::WorkingTimeItem() {

}

WorkingTimeItem::WorkingTimeItem(QString id) {
    this->id = id;
}

WorkingTimeItem::WorkingTimeItem(QString username, QDateTime start, QDateTime end, hypha::database::Database *database, QWidget *parent):    QWidget(parent),
    ui(new Ui::WorkingTimeItem) {
    ui->setupUi(this);
    this->database = database;
    this->username = username;
    this->start = start;
    this->end = end;
    init();
}

WorkingTimeItem::WorkingTimeItem(QString username, QDateTime start, QDateTime end, QString type, hypha::database::Database *database, QWidget *parent):    QWidget(parent),
    ui(new Ui::WorkingTimeItem) {
    ui->setupUi(this);
    this->database = database;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    init();
}

WorkingTimeItem::WorkingTimeItem(QString id, QString username, QDateTime start, QDateTime end, QString type, hypha::database::Database *database, QWidget *parent):    QWidget(parent),
    ui(new Ui::WorkingTimeItem) {
    ui->setupUi(this);
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->database = database;
    init();
}

WorkingTimeItem::~WorkingTimeItem() {
    delete ui;
}

void WorkingTimeItem::save() {
    Poco::Data::Statement statement = database->getStatement();
    if (id.isEmpty()) {
        statement << "insert into workingtime(username, type, start, end) values(?, ?, ?, ?);",
                  Poco::Data::use(this->username.toStdString()), Poco::Data::use(this->ui->typeComboBox->currentText().toStdString()),
                  Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                  Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString());
    } else {
        statement << "update workingtime set username=?, type=?, start=?, end=? where id=?;",
                  Poco::Data::use(this->username.toStdString()), Poco::Data::use(this->ui->typeComboBox->currentText().toStdString()),
                  Poco::Data::use(ui->startDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                  Poco::Data::use(ui->endDateTimeEdit->dateTime().toUTC().toString().toStdString()),
                  Poco::Data::use(this->id.toStdString());
    }
    statement.execute();
}

void WorkingTimeItem::deleteFromDatabase() {
    if (id.isEmpty()) {
    } else {
        Poco::Data::Statement statement = database->getStatement();
        statement << "delete from workingtime where id = ?;",
                  Poco::Data::use(this->id.toStdString());
        statement.execute();
    }
}

void WorkingTimeItem::init() {
    ui->startDateTimeEdit->setDateTime(start.toLocalTime());
    ui->endDateTimeEdit->setDateTime(end.toLocalTime());
    ui->typeComboBox->setCurrentText(type);
}
