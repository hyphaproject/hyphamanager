#ifndef WIFIWIDGET_H
#define WIFIWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class WifiWidget;
}

class WifiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WifiWidget(QWidget *parent = 0);
    ~WifiWidget();

private:
    Ui::WifiWidget *ui;
};

#endif // WIFIWIDGET_H
