// Copyright (c) 2015-2016 Hypha
#include "rpiledwidget.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "ui_rpiledwidget.h"

RpiLedWidget::RpiLedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RpiLedWidget) {
  ui->setupUi(this);
}

RpiLedWidget::~RpiLedWidget() { delete ui; }

void RpiLedWidget::setHost(QString host) { this->host = host; }

void RpiLedWidget::loadConfig(QString json) {
  QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
  QJsonObject object = document.object();
  if (object.contains("user")) {
  }
}

QString RpiLedWidget::getConfig() { return "{}"; }
