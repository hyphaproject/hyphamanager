// Copyright (c) 2015-2016 Hypha
#include "main/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AboutDialog) {
  ui->setupUi(this);
}

AboutDialog::~AboutDialog() { delete ui; }
