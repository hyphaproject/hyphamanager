#ifndef AUTOHANDLERWIDGET_H
#define AUTOHANDLERWIDGET_H

#include <map>
#include <string>
#include <QWidget>
#include <hypha/handler/hyphahandler.h>

namespace Ui {
class AutoHandlerWidget;
}

class AutoHandlerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutoHandlerWidget(hypha::handler::HyphaHandler * handler, QWidget *parent = 0);
    ~AutoHandlerWidget();
    void setupUi();
    void loadConfig(std::string json);
    std::string getConfig();

protected:
    void addWidgets(QWidget* widget1, QWidget* widget2);

private:
    hypha::handler::HyphaHandler * handler;
    Ui::AutoHandlerWidget *ui;
    std::map<std::string, QWidget*> items;
};

#endif // AUTOHANDLERWIDGET_H
