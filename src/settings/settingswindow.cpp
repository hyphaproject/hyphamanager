#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(HyphaManagerSettings * settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    this->settings = settings;
    ui->setupUi(this);
    load();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::load()
{
    ui->serverLineEdit->setText(settings->getValue("email", "host", "localhost").toString());
    ui->usernameLineEdit->setText(settings->getValue("email", "user", "").toString());
    ui->passwordLineEdit->setText(settings->getValue("email", "password", "").toString());
}

void SettingsWindow::on_buttonBox_accepted()
{
    settings->setValue("email", "host", ui->serverLineEdit->text());
    settings->setValue("email", "user", ui->usernameLineEdit->text());
    settings->setValue("email", "password", ui->passwordLineEdit->text());
}
