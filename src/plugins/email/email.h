#ifndef EMAIL_H
#define EMAIL_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "emailwidget.h"
namespace hypha{
namespace plugin{
namespace email{
class EMail : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.email" FILE "email.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "email"; }
    QString getTitle() { return "EMail"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to send emails.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    EMailWidget * emailWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // EMAIL_H
