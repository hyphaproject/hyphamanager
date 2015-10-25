#ifndef EXPLORENFCWIDGET_H
#define EXPLORENFCWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class ExploreNFCWidget;
}

class ExploreNFCWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ExploreNFCWidget(QWidget *parent = 0);
  ~ExploreNFCWidget();

 private:
  Ui::ExploreNFCWidget *ui;
};

#endif // EXPLORENFCWIDGET_H
