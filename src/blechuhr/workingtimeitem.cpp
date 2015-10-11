#include "workingtimeitem.h"
#include "ui_workingtimeitem.h"

WorkingTimeItem::WorkingTimeItem(){

}

WorkingTimeItem::WorkingTimeItem(QString id)
{
    this->id = id;
}



WorkingTimeItem::WorkingTimeItem(QString username, QDateTime start, QDateTime end, Database *database, QWidget *parent):    QWidget(parent),
    ui(new Ui::WorkingTimeItem)
{
    ui->setupUi(this);
    this->database = database;
    this->username = username;
    this->start = start;
    this->end = end;
    init();
}

WorkingTimeItem::WorkingTimeItem(QString username, QDateTime start, QDateTime end, QString type, Database *database, QWidget *parent):    QWidget(parent),
    ui(new Ui::WorkingTimeItem)
{
    ui->setupUi(this);
    this->database = database;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    init();
}

WorkingTimeItem::WorkingTimeItem(QString id, QString username, QDateTime start, QDateTime end, QString type, Database *database, QWidget *parent):    QWidget(parent),
    ui(new Ui::WorkingTimeItem)
{
    ui->setupUi(this);
    this->id = id;
    this->username = username;
    this->start = start;
    this->end = end;
    this->type = type;
    this->database = database;
    init();
}

WorkingTimeItem::~WorkingTimeItem()
{
    delete ui;
}

void WorkingTimeItem::save()
{
    QSqlQuery query = database->getQuery();
    if(id.isEmpty()){
        query.prepare("insert into workingtime(username, type, start, end) values(:username, :type, :start, :end);");
        query.bindValue(":username", this->username);
        query.bindValue(":type", ui->typeComboBox->currentText());
        query.bindValue(":start", ui->startDateTimeEdit->dateTime().toUTC());
        query.bindValue(":end", ui->endDateTimeEdit->dateTime().toUTC());
    }else{
        query.prepare("update workingtime set username=:username, type=:type, start=:start, end=:end where id = :id;");
        query.bindValue(":username", this->username);
        query.bindValue(":type", ui->typeComboBox->currentText());
        query.bindValue(":start", ui->startDateTimeEdit->dateTime().toUTC());
        query.bindValue(":end", ui->endDateTimeEdit->dateTime().toUTC());
        query.bindValue(":id", this->id);
    }
    query.exec();
}

void WorkingTimeItem::deleteFromDatabase()
{
    QSqlQuery query = database->getQuery();
    if(id.isEmpty()){
    }else{
        query.prepare("delete from workingtime where id = :id;");
        query.bindValue(":id", this->id);
        query.exec();
    }
}

void WorkingTimeItem::init()
{
    ui->startDateTimeEdit->setDateTime(start.toLocalTime());
    ui->endDateTimeEdit->setDateTime(end.toLocalTime());
    ui->typeComboBox->setCurrentText(type);
}
