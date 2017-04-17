// Copyright (c) 2015-2016 Hypha
#include "plugin/unknownpluginwidget.h"
#include "ui_unknownpluginwidget.h"

UnknownPluginWidget::UnknownPluginWidget(std::string pluginId, QWidget *parent)
    : QWidget(parent), ui(new Ui::UnknownPluginWidget) {
  ui->setupUi(this);
  this->pluginId = pluginId;
  ui->pluginIdLabel->setText(QString::fromStdString(pluginId));
}

UnknownPluginWidget::~UnknownPluginWidget() { delete ui; }

void UnknownPluginWidget::loadConfig(std::string json) {
  ui->textBrowser->setText(QString::fromStdString(json));
}

std::string UnknownPluginWidget::getConfig() {
  return ui->textBrowser->toPlainText().toStdString();
}
