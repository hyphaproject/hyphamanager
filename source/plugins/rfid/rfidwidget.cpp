#include "rfidwidget.h"
#include "ui_rfidwidget.h"

RFIDWidget::RFIDWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RFIDWidget) {
  ui->setupUi(this);
}

RFIDWidget::~RFIDWidget() { delete ui; }
