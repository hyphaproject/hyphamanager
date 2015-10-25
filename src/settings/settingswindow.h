#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H


#include <QDialog>
#include <hypha/settings/hyphasettings.h>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog {
    Q_OBJECT

  public:
    explicit SettingsWindow(hypha::settings::HyphaSettings * settings, QWidget *parent = 0);
    ~SettingsWindow();
    void load();

  private:
    Ui::SettingsWindow *ui;
  protected:
    hypha::settings::HyphaSettings * settings;
  private slots:
    void on_buttonBox_accepted();
};

#endif // SETTINGSWINDOW_H
