#include "rpigpiowidget.h"
#include "ui_rpigpiowidget.h"

RpiGpioWidget::RpiGpioWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::RpiGpioWidget) {
  ui->setupUi(this);
}

RpiGpioWidget::~RpiGpioWidget() { delete ui; }
