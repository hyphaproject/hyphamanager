#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H


#include <QDialog>
#include "hyphamanagersettings.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(HyphaManagerSettings * settings, QWidget *parent = 0);
    ~SettingsWindow();
    void load();

private:
    Ui::SettingsWindow *ui;
protected:
    HyphaManagerSettings * settings;
private slots:
    void on_buttonBox_accepted();
};

#endif // SETTINGSWINDOW_H
