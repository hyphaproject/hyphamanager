#ifndef AUTOPLUGINWIDGET_H
#define AUTOPLUGINWIDGET_H

#include <map>
#include <string>
#include <QWidget>
#include <hypha/plugin/hyphaplugin.h>

namespace Ui {
class AutoPluginWidget;
}

class AutoPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutoPluginWidget(hypha::plugin::HyphaPlugin * plugin, QWidget *parent = 0);
    ~AutoPluginWidget();
    void setupUi();
    void loadConfig(std::string json);
    std::string getConfig();

protected:
    void addWidgets(QWidget* widget1, QWidget* widget2 = nullptr);

private:
    hypha::plugin::HyphaPlugin * plugin;
    Ui::AutoPluginWidget *ui;
    std::map<std::string, QWidget*> items;
};

#endif // AUTOPLUGINWIDGET_H
