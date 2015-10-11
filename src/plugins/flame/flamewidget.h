#ifndef FLAMEWIDGET_H
#define FLAMEWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class FlameWidget;
}

class FlameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlameWidget(QWidget *parent = 0);
    ~FlameWidget();
    void setHost(QString host);
    void loadConfig(QString json);
    QString getConfig();
private:
    Ui::FlameWidget *ui;
    QString host;
};

#endif // FLAMEWIDGET_H
