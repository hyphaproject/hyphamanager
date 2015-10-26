#include "espeakwidget.h"
#include "ui_espeakwidget.h"

ESpeakWidget::ESpeakWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ESpeakWidget) {
    ui->setupUi(this);
}

ESpeakWidget::~ESpeakWidget() {
    delete ui;
}
