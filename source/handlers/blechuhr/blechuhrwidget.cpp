#include "blechuhrwidget.h"
#include "ui_blechuhrwidget.h"

BlechUhrWidget::BlechUhrWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlechUhrWidget) {
    ui->setupUi(this);
}

BlechUhrWidget::~BlechUhrWidget() {
    delete ui;
}