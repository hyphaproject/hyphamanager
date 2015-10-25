#ifndef DHT11WIDGET_H
#define DHT11WIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class Dht11Widget;
}

class Dht11Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Dht11Widget(QWidget *parent = 0);
  ~Dht11Widget();
  void setHost(QString host);
  void loadConfig(QString json);
  QString getConfig();
 private:
  Ui::Dht11Widget *ui;
  QString host;
};

#endif // DHT11WIDGET_H
