// Copyright (c) 2015-2016 Hypha
#include "explorenfcwidget.h"
#include "ui_explorenfcwidget.h"

ExploreNFCWidget::ExploreNFCWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ExploreNFCWidget) {
  ui->setupUi(this);
}

ExploreNFCWidget::~ExploreNFCWidget() { delete ui; }
