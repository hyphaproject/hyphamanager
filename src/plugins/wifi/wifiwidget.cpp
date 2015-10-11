#include "wifiwidget.h"
#include "ui_wifiwidget.h"

WifiWidget::WifiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WifiWidget)
{
    ui->setupUi(this);
}

WifiWidget::~WifiWidget()
{
    delete ui;
}
