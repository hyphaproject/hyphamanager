#ifndef SERVERSTATUSWIDGET_H
#define SERVERSTATUSWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class ServerStatusWidget;
}

class ServerStatusWidget : public QWidget {
    Q_OBJECT

  public:
    explicit ServerStatusWidget(QWidget *parent = 0);
    ~ServerStatusWidget();
    void loadConfig(QString config);
    QString getConfig();

  private:
    Ui::ServerStatusWidget *ui;
};

#endif // SERVERSTATUSWIDGET_H
