#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(hypha::settings::HyphaSettings * settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow) {
    this->settings = settings;
    ui->setupUi(this);
    load();
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}

void SettingsWindow::load() {
    ui->serverLineEdit->setText(QString::fromStdString(
                                    settings->getString("email:host", "localhost")));
    ui->usernameLineEdit->setText(QString::fromStdString(
                                      settings->getString("email:user", "")));
    ui->passwordLineEdit->setText(QString::fromStdString(
                                      settings->getString("email:password", "")));
}

void SettingsWindow::on_buttonBox_accepted() {
    std::string host = ui->serverLineEdit->text().toStdString();
    settings->setString("email.host", host);
    std::string user =  ui->usernameLineEdit->text().toStdString();
    settings->setString("email.user", user);
    std::string password = ui->passwordLineEdit->text().toStdString();
    settings->setString("email.password", password);
}
