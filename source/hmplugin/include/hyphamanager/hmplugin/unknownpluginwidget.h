#ifndef UNKNOWNPLUGINWIDGET_H
#define UNKNOWNPLUGINWIDGET_H

#include <QWidget>
#include <string>
#include <hyphamanager/hmplugin/hmplugin_api.h>

namespace Ui {
class UnknownPluginWidget;
}

class HMPLUGIN_API UnknownPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnknownPluginWidget(QWidget *parent = 0);
    ~UnknownPluginWidget();
    void loadConfig(std::string json);
    std::string getConfig();

private:
    Ui::UnknownPluginWidget *ui;
};

#endif // UNKNOWNPLUGINWIDGET_H
