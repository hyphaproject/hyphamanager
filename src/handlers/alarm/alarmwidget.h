#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class AlarmWidget;
}

class AlarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmWidget(QWidget *parent = 0);
    ~AlarmWidget();
    void loadConfig(QString config);
    QString getConfig();

private:
    Ui::AlarmWidget *ui;
};

#endif // ALARMWIDGET_H
