#ifndef FINGERPRINTZFMWIDGET_H
#define FINGERPRINTZFMWIDGET_H

#include <QtWidgets/QWidget>

namespace Ui {
class FingerPrintZFMWidget;
}

class FingerPrintZFMWidget : public QWidget {
  Q_OBJECT

 public:
  explicit FingerPrintZFMWidget(QWidget *parent = 0);
  ~FingerPrintZFMWidget();

 private:
  Ui::FingerPrintZFMWidget *ui;
};

#endif // FINGERPRINTZFMWIDGET_H
