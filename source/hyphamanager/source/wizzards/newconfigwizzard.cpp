// Copyright (c) 2015-2016 Hypha
#include "wizzards/newconfigwizzard.h"
#include <QFileDialog>
#include "hypha/core/settings/configgenerator.h"
#include "ui_newconfigwizzard.h"

NewConfigWizzard::NewConfigWizzard(QWidget *parent)
    : QDialog(parent), ui(new Ui::NewConfigWizzard) {
  ui->setupUi(this);
}

NewConfigWizzard::~NewConfigWizzard() { delete ui; }

void NewConfigWizzard::on_selectFileButton_clicked() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Config File"), ui->configFileEdit->text(),
      tr("Hypha Config File (*.xml)"));
  if (!fileName.isEmpty()) ui->configFileEdit->setText(fileName);
}

void NewConfigWizzard::on_selectDBButton_clicked() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("SQLite File"),
                                                  ui->dHostEdit->text(),
                                                  tr("SQLite File (*.sqlite)"));
  if (!fileName.isEmpty()) ui->dDatabaseEdit->setText(fileName);
}

void NewConfigWizzard::on_selectUserDBButton_clicked() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("SQLite File"),
                                                  ui->udHostEdit->text(),
                                                  tr("SQLite File (*.sqlite)"));
  if (!fileName.isEmpty()) ui->udDatabaseEdit->setText(fileName);
}

void NewConfigWizzard::on_cancelButton_clicked() { this->reject(); }

void NewConfigWizzard::on_nextButton_clicked() {
  if (ui->tabWidget->currentIndex() == ui->tabWidget->count() - 1) {
    hypha::settings::ConfigGenerator generator;
    generator.dbDatabase = ui->dDatabaseEdit->text().toStdString();
    generator.dbDriver = ui->dDriverBox->currentText().toStdString();
    generator.dbHost = ui->dHostEdit->text().toStdString();
    generator.dbPassword = ui->dPasswordEdit->text().toStdString();
    generator.dbUsername = ui->dUsernameEdit->text().toStdString();

    generator.udbAttributeDevices = ui->udAttrDevicesEdit->text().toStdString();
    generator.udbAttributeFirstname =
        ui->udAttrFirstnameEdit->text().toStdString();
    generator.udbAttributeLastname =
        ui->udAttrLastnameEdit->text().toStdString();
    generator.udbAttributeMail = ui->udAttrMailEdit->text().toStdString();
    generator.udbAttributeUsername =
        ui->udAttrUsernameEdit->text().toStdString();
    generator.udbDatabase = ui->udDatabaseEdit->text().toStdString();
    generator.udbDriver = ui->udDriverBox->currentText().toStdString();
    generator.udbHost = ui->udHostEdit->text().toStdString();
    generator.udbPassword = ui->udPasswordEdit->text().toStdString();
    generator.udbTable = ui->udTableEdit->text().toStdString();
    generator.generateConfigFile(ui->configFileEdit->text().toStdString());

    this->accept();
  } else {
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);
  }
}
