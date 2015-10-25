#ifndef BLECHUHRWIDGET_H
#define BLECHUHRWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class BlechUhrWidget;
}

class BlechUhrWidget : public QWidget {
    Q_OBJECT

  public:
    explicit BlechUhrWidget(QWidget *parent = 0);
    ~BlechUhrWidget();

  private:
    Ui::BlechUhrWidget *ui;
};

#endif // BLECHUHRWIDGET_H
