#ifndef UNKNOWNHANDLERWIDGET_H
#define UNKNOWNHANDLERWIDGET_H

#include <QWidget>

namespace Ui {
class UnknownHandlerWidget;
}

class UnknownHandlerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UnknownHandlerWidget(QWidget *parent = 0);
    ~UnknownHandlerWidget();
    void loadConfig(std::string json);
    std::string getConfig();

private:
    Ui::UnknownHandlerWidget *ui;
};

#endif // UNKNOWNHANDLERWIDGET_H
