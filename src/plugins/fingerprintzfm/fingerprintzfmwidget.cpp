#include "fingerprintzfmwidget.h"
#include "ui_fingerprintzfmwidget.h"

FingerPrintZFMWidget::FingerPrintZFMWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FingerPrintZFMWidget) {
  ui->setupUi(this);
}

FingerPrintZFMWidget::~FingerPrintZFMWidget() {
  delete ui;
}
