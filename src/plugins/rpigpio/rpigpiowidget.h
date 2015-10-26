#ifndef RPIGPIOWIDGET_H
#define RPIGPIOWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class RpiGpioWidget;
}

class RpiGpioWidget : public QWidget {
    Q_OBJECT

  public:
    explicit RpiGpioWidget(QWidget *parent = 0);
    ~RpiGpioWidget();

  private:
    Ui::RpiGpioWidget *ui;
};

#endif // RPIGPIOWIDGET_H
