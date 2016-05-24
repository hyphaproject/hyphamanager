#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QFileDialog>

SettingsWindow::SettingsWindow(hypha::settings::HyphaSettings *settings, QWidget *parent) :
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
                                    settings->getString("email.host", "localhost")));
    ui->usernameLineEdit->setText(QString::fromStdString(
                                      settings->getString("email.user", "")));
    ui->passwordLineEdit->setText(QString::fromStdString(
                                      settings->getString("email.password", "")));

    ui->handlersPathEdit->setText(QString::fromStdString(
                                      settings->getString("system.handlerspath", "hyphahandlers/")));
    ui->pluginsPathEdit->setText(QString::fromStdString(
                                      settings->getString("system.pluginspath", "hyphaplugins/")));

}

void SettingsWindow::on_buttonBox_accepted() {
    std::string host = ui->serverLineEdit->text().toStdString();
    settings->setString("email.host", host);
    std::string user =  ui->usernameLineEdit->text().toStdString();
    settings->setString("email.user", user);
    std::string password = ui->passwordLineEdit->text().toStdString();
    settings->setString("email.password", password);

    std::string handlerspath = ui->handlersPathEdit->text().toStdString();
    settings->setString("system.handlerspath", handlerspath);

    std::string pluginspath = ui->pluginsPathEdit->text().toStdString();
    settings->setString("system.pluginspath", pluginspath);

    settings->save();
}

void SettingsWindow::on_handlersButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "select handlers path", ui->handlersPathEdit->text());
    ui->handlersPathEdit->setText(path);
}

void SettingsWindow::on_pluginsButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "select plugins path", ui->pluginsPathEdit->text());
    ui->pluginsPathEdit->setText(path);
}
