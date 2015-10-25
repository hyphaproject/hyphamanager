#ifndef EXPORTWIDGET_H
#define EXPORTWIDGET_H

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItemModel>
#include "main/instance.h"

namespace Ui {
class ExportWidget;
}

class ExportWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ExportWidget(Instance *instance, QWidget *parent = 0);
  ~ExportWidget();


 protected:
  Instance *instance;
  QStandardItemModel listModel;

  void init();
  void loadUser();
  QString getSaveDir();
  QString exportRFID_to_CSV(QString username, QDate month, QString folder);
  QString exportRFID_to_PDF(QString username, QDate month, QString folder);
  QString exportReport_to_PDF(QString username, QDate month, QString folder);

 private slots:
  void on_allUserCheckBox_toggled(bool checked);

  void on_dateFromEdit_userDateChanged(const QDate &date);

  void on_filesButton_clicked();

  void on_emailButton_clicked();

 private:
  Ui::ExportWidget *ui;
};

#endif // EXPORTWIDGET_H
