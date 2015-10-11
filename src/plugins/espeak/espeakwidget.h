#ifndef ESPEAKWIDGET_H
#define ESPEAKWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class ESpeakWidget;
}

class ESpeakWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ESpeakWidget(QWidget *parent = 0);
    ~ESpeakWidget();

private:
    Ui::ESpeakWidget *ui;
};

#endif // ESPEAKWIDGET_H
