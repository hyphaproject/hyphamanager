// Copyright (c) 2015-2016 Hypha
#include "hyphamanager/hmhandler/unknownhandlerwidget.h"
#include "ui_unknownhandlerwidget.h"

UnknownHandlerWidget::UnknownHandlerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::UnknownHandlerWidget) {
  ui->setupUi(this);
}

UnknownHandlerWidget::~UnknownHandlerWidget() { delete ui; }

void UnknownHandlerWidget::loadConfig(std::string json) {
  ui->textBrowser->setText(QString::fromStdString(json));
}

std::string UnknownHandlerWidget::getConfig() {
  return ui->textBrowser->toPlainText().toStdString();
}
