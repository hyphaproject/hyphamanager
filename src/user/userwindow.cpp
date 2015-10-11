#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidgetItem>
#include <QtSql/QSqlQuery>
#include <QtCore/QDateTime>
#include <QtCore/QTimeZone>
#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(Instance * instance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    this->instance = instance;
    reload();
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::reload()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(instance->getUserDatabase()->getUsers());
    loadOnline();
}

void UserWindow::loadOnline()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        QListWidgetItem * item = ui->listWidget->item(i);
        if(isOnline(item->text())){
            item->setIcon(QIcon(":/users/images/actions/online.svg"));
            item->setToolTip("present since: " + this->lastConnection(item->text()));
        }
    }
}

bool UserWindow::isOnline(QString username)
{
    QList<QString> devices = instance->getUserDatabase()->getDevices(username);
    // number of registrations today
    int connections = 0;
    for(int i = 0; i< instance->getUserDatabase()->getDevices(username).size(); ++i){
        QString device = devices.at(i);
        QSqlQuery query = instance->getDatabase()->getQuery();
            query.prepare("select count(id) from deviceonline where deviceid='"+device+"' and DATE(time) = '" +QDateTime::currentDateTimeUtc().date().toString("yyyy-MM-dd")+"'" );
            query.exec();
            while( query.next() ){
                connections += query.value(0).toInt();
            }
    }
    return connections % 2 == 1;
}

void UserWindow::reloadUserStatus(QString username)
{
    QList<QString> devices = instance->getUserDatabase()->getDevices(username);
    QDateTime datetime;
    for(int i = 0; i< instance->getUserDatabase()->getDevices(username).size(); ++i){
        QString device = devices.at(i);
        QSqlQuery query = instance->getDatabase()->getQuery();
            query.prepare("select time from deviceonline where deviceid='"+device+"' ORDER BY time desc" );
            query.exec();
            while( query.next() ){
                QDateTime dt = query.value(0).toDateTime();
                dt.setTimeSpec(Qt::UTC);
                if(dt > datetime){
                    ui->deviceOnlineLabel->setText(device);
                    ui->dateTimeEdit->setDateTime(dt.toLocalTime());
                    datetime = dt;
                }
                break;
            }
    }
}

QString UserWindow::lastConnection(QString username)
{
    QList<QString> devices = instance->getUserDatabase()->getDevices(username);
    QDateTime datetime;
    for(int i = 0; i< instance->getUserDatabase()->getDevices(username).size(); ++i){
        QString device = devices.at(i);
        QSqlQuery query = instance->getDatabase()->getQuery();
            query.prepare("select time from deviceonline where deviceid='"+device+"' ORDER BY time desc" );
            query.exec();
            while( query.next() ){
                QDateTime dt = query.value(0).toDateTime();
                dt.setTimeSpec(Qt::UTC);
                if(dt > datetime){
                    datetime = dt;
                }
                break;
            }
    }
    return datetime.toLocalTime().toString("hh:mm");
}

void UserWindow::on_newUserButton_clicked()
{
    QString username = QInputDialog::getText(this, "New User", "Username");
    if(instance->getUserDatabase()->createUser(username, "Unknown", "Unknown", "")){
        reload();
    }else{
        QMessageBox::warning(this, "Error", "The user could not been added to the database.");
    }
}

void UserWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->groupBox->setTitle(currentText);
    ui->firstnameEdit->setText(instance->getUserDatabase()->getFirstname(currentText));
    ui->lastnameEdit->setText(instance->getUserDatabase()->getLastname(currentText));
    ui->mailEdit->setText(instance->getUserDatabase()->getMail(currentText));
    QStringList devs = instance->getUserDatabase()->getDevices(currentText);
    ui->deviceIdEdit->setText(devs.join(","));
    ui->saveButton->setEnabled(false);
    reloadUserStatus(currentText);
}

void UserWindow::on_firstnameEdit_editingFinished()
{
    ui->saveButton->setEnabled(true);
}

void UserWindow::on_lastnameEdit_editingFinished()
{
    ui->saveButton->setEnabled(true);
}

void UserWindow::on_mailEdit_editingFinished()
{
    ui->saveButton->setEnabled(true);
}

void UserWindow::on_deviceIdEdit_editingFinished()
{
    ui->saveButton->setEnabled(true);
}

void UserWindow::on_saveButton_clicked()
{
    if(instance->getUserDatabase()->updateUser(ui->groupBox->title(), ui->firstnameEdit->text(), ui->lastnameEdit->text(), ui->mailEdit->text(), ui->deviceIdEdit->text()))
        ui->saveButton->setEnabled(false);
}
