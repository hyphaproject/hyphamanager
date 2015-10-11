#include "summarywidget.h"
#include "ui_summarywidget.h"
#include "workingtimealgo.h"
#include "workingtimeitem.h"
#include "summarymonth.h"

SummaryWidget::SummaryWidget(QString username, Database * database, UserDatabase * userDatabase, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SummaryWidget)
{
    this->username = username;
    this->database = database;
    this->userDatabase = userDatabase;
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    ui->usernameEdit->setText(username);
    ui->emailEdit->setText(userDatabase->getMail(username));
    reloadSummary();
}

SummaryWidget::~SummaryWidget()
{
    delete ui;
}

void SummaryWidget::reloadSummary()
{
    WorkingTimeAlgo algo(database, userDatabase);
    algo.setUsername(username);
    algo.setDate(ui->dateEdit->date());

    ui->timesListWidget->clear();
    foreach(WorkingTime wt, algo.getMonth()){
        QListWidgetItem *item = new QListWidgetItem(ui->timesListWidget);
        ui->timesListWidget->addItem(item);
        WorkingTimeItem *workingTimeItem = new WorkingTimeItem(wt.getUsername(), wt.getStart(), wt.getEnd(), wt.getType(), database);
        item->setSizeHint(workingTimeItem->minimumSizeHint());
        ui->timesListWidget->setItemWidget(item, workingTimeItem);
    }
    calculateWorkingHours();
}

void SummaryWidget::calculateWorkingHours()
{
    SummaryMonth summary(database, userDatabase);
    summary.setUsername(username);
    summary.setDate(ui->dateEdit->date());
    summary.calculate();
    ui->workedHoursEdit->setText(QString::number( summary.getWorkedHours(), 'f', 2 ));
}

QDate SummaryWidget::getSelectedDate()
{
    return ui->dateEdit->date();
}

void SummaryWidget::on_dateEdit_editingFinished()
{
    reloadSummary();
}
