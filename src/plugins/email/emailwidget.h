#ifndef EMAILWIDGET_H
#define EMAILWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class EMailWidget;
}

class EMailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EMailWidget(QWidget *parent = 0);
    ~EMailWidget();
    void setHost(QString host);
    void loadConfig(QString json);
    QString getConfig();
private:
    Ui::EMailWidget *ui;
    QString host;
};

#endif // EMAILWIDGET_H
