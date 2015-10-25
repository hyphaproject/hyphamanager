#include <hypha/database/database.h>
#include "workingtimeadddialog.h"
#include "ui_workingtimeadddialog.h"
#include <QtCore/QDateTime>

WorkingTimeAddDialog::WorkingTimeAddDialog(QString username, QDate date, hypha::database::Database *database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkingTimeAddDialog)
{
    this->username = username;
    this->date = date;
    this->database = database;
    ui->setupUi(this);
    init();
}

WorkingTimeAddDialog::~WorkingTimeAddDialog()
{
    delete workingTimeItem;
    delete ui;
}

void WorkingTimeAddDialog::init()
{
    this->workingTimeItem = new WorkingTimeItem(username, QDateTime(date), QDateTime(date), database);
    ui->center->addWidget(workingTimeItem);
}

void WorkingTimeAddDialog::on_buttonBox_accepted()
{
    workingTimeItem->save();
}
