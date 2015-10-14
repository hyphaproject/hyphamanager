#include <QFileDialog>
#include "newconfigwizzard.h"
#include "ui_newconfigwizzard.h"

NewConfigWizzard::NewConfigWizzard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewConfigWizzard)
{
    ui->setupUi(this);
}

NewConfigWizzard::~NewConfigWizzard()
{
    delete ui;
}

void NewConfigWizzard::on_selectFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Config File"), ui->configFileEdit->text(), tr("INI File (*.ini)"));
    if(!fileName.isEmpty()) ui->configFileEdit->setText(fileName);
}

void NewConfigWizzard::on_selectDBButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("SQLite File"), ui->dHostEdit->text(), tr("SQLite File (*.sqlite)"));
    if(!fileName.isEmpty()) ui->dHostEdit->setText(fileName);
}

void NewConfigWizzard::on_selectUserDBButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("SQLite File"), ui->udHostEdit->text(), tr("SQLite File (*.sqlite)"));
    if(!fileName.isEmpty()) ui->udHostEdit->setText(fileName);
}
