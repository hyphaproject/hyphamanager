#include "hyphamanager/hmplugin/unknownpluginwidget.h"
#include "ui_unknownpluginwidget.h"

UnknownPluginWidget::UnknownPluginWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::UnknownPluginWidget) {
  ui->setupUi(this);
}

UnknownPluginWidget::~UnknownPluginWidget() { delete ui; }

void UnknownPluginWidget::loadConfig(std::string json) {
  ui->textBrowser->setText(QString::fromStdString(json));
}

std::string UnknownPluginWidget::getConfig() {
  return ui->textBrowser->toPlainText().toStdString();
}
